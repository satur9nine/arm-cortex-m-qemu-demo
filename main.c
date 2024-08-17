/*
 * FreeRTOS V202212.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the standard demo application tasks.
 * In addition to the standard demo tasks, the following tasks and tests are
 * defined and/or created within this file:
 *
 * "OLED" task - the OLED task is a 'gatekeeper' task.  It is the only task that
 * is permitted to access the display directly.  Other tasks wishing to write a
 * message to the OLED send the message on a queue to the OLED task instead of
 * accessing the OLED themselves.  The OLED task just blocks on the queue waiting
 * for messages - waking and displaying the messages as they arrive.
 *
 * "Check" hook -  This only executes every five seconds from the tick hook.
 * Its main function is to check that all the standard demo tasks are still
 * operational.  Should any unexpected behaviour within a demo task be discovered
 * the tick hook will write an error to the OLED (via the OLED task).  If all the
 * demo tasks are executing with their expected behaviour then the check task
 * writes PASS to the OLED (again via the OLED task), as described above.
 *
 * Use the following command to start running the application in QEMU, pausing
 * to wait for a debugger connection:
 * "qemu-system-arm -machine lm3s6965evb -s -S -kernel [pat_to]\RTOSDemo.elf"
 *
 * To enable FreeRTOS+Trace:
 *  1) Add #include "trcRecorder.h" to the bottom of FreeRTOSConfig.h.
 *  2) Call vTraceEnable( TRC_START ); at the top of main.
 *  3) Ensure the "FreeRTOS+Trace Recorder" folder in the Project Explorer
 *     window is not excluded from the build.
 *
 * To retrieve the trace files:
 *	1) Use the Memory windows in the Debug perspective to dump RAM from the
 *	   RecorderData variable.
 */

/*************************************************************************
* Please ensure to read http://www.freertos.org/portlm3sx965.html
* which provides information on configuring and running this demo for the
* various Luminary Micro EKs.
*************************************************************************/

/* Standard includes. */
#include <stdio.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* Hardware library includes. */
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_sysctl.h"
#include "hw_uart.h"
#include "sysctl.h"
#include "gpio.h"
#include "grlib.h"
#include "osram128x64x4.h"
#include "uart.h"

/* Demo app includes. */
#include "bitmap.h"

/* Other stuff */
#include "cm_backtrace.h"
#include "backtrace.h"

/*-----------------------------------------------------------*/

// Test backtrace with a crash
//#define CRASH

// Test backtrace with an infinite loop
#define DEMO_INFINTE_LOOP

/* The time between cycles of the 'check' functionality (defined within the
 * tick hook. */
#define mainCHECK_DELAY                        ( ( TickType_t ) 2000 / portTICK_PERIOD_MS )

/* Task stack sizes. */
#define mainOLED_TASK_STACK_SIZE               ( configMINIMAL_STACK_SIZE + 40 )

/* Task priorities. */
#define mainCHECK_TASK_PRIORITY                ( tskIDLE_PRIORITY + 3 )
#define mainSEM_TEST_PRIORITY                  ( tskIDLE_PRIORITY + 1 )
#define mainCREATOR_TASK_PRIORITY              ( tskIDLE_PRIORITY + 3 )
#define mainGEN_QUEUE_TASK_PRIORITY            ( tskIDLE_PRIORITY )

/* The maximum number of message that can be waiting for display at any one
 * time. */
#define mainOLED_QUEUE_SIZE                    ( 3 )

/* Dimensions the buffer into which the jitter time is written. */
#define mainMAX_MSG_LEN                        25

/* The period of the system clock in nano seconds.  This is used to calculate
 * the jitter time in nano seconds. */
#define mainNS_PER_CLOCK                       ( ( uint32_t ) ( ( 1.0 / ( double ) configCPU_CLOCK_HZ ) * 1000000000.0 ) )

/* Constants used when writing strings to the display. */
#define mainCHARACTER_HEIGHT                   ( 9 )
#define mainMAX_ROWS_128                       ( mainCHARACTER_HEIGHT * 14 )
#define mainMAX_ROWS_96                        ( mainCHARACTER_HEIGHT * 10 )
#define mainMAX_ROWS_64                        ( mainCHARACTER_HEIGHT * 7 )
#define mainFULL_SCALE                         ( 15 )
#define ulSSI_FREQUENCY                        ( 3500000UL )

/*-----------------------------------------------------------*/

/*
 * Configures the high frequency timers - those used to measure the timing
 * jitter while the real time kernel is executing.
 */
extern void vSetupHighFrequencyTimer( void );

/*-----------------------------------------------------------*/

/* The queue used to send messages to the OLED task. */
static QueueHandle_t xOLEDQueue;

/* The welcome text. */
const char * const pcWelcomeMessage = "   www.FreeRTOS.org";

static TaskHandle_t prvOLEDTaskHandle;

static TaskHandle_t prvDemoTaskHandle;

/*-----------------------------------------------------------*/

static void vInspectionTask( void * pvParameters )
{
    (void) pvParameters;

    while (1) {
        vTaskDelay(3000);

        cm_backtrace_print_call_stack_for_thread(prvDemoTaskHandle);
    }
}
/*-----------------------------------------------------------*/

volatile uint32_t g_temp;
uint32_t g_stack_start_addr;
uint32_t g_stack_size;

void spin(void)
{

    register long r4 asm ("r4");
    r4 = 0x44444444;
    register long r5 asm ("r5");
    r5 = 0x55555555;
    register long r6 asm ("r6");
    r6 = 0x66666666;
    // Skip r7, it is the FP
    register long r8 asm ("r8");
    r8 = 0x88888888;
    register long r9 asm ("r9");
    r9 = 0x99999999;
    register long r10 asm ("r10");
    r10 = 0xAAAAAAAA;
    register long r11 asm ("r11");
    r11 = 0xBBBBBBBB;

    while (1) {
        g_temp = 99;

        // Never true but compiler doesn't know since g_temp is volatile
        if (g_temp == 0) {
            return;
        }
    }
}

void intermediate2(void)
{
    spin();
    printf("exiting intermediate2\n");
}

void intermediate1(void)
{
    intermediate2();
    printf("exiting intermediate1\n");
}

void vDemoBacktrace(void * pvParameters)
{
    (void) pvParameters;

    g_stack_start_addr = (uint32_t) vTaskStackAddr();
    g_stack_size = vTaskStackSize() * sizeof( StackType_t );

#ifdef DEMO_CRASH

    // Jump to reserved memory... nothing to execute so crashes
    void(* explode)(void) = (void (*)(void)) 0x10000000;
    explode();

#endif

    while (1) {
        g_temp = 99;

        // Never true but compiler doesn't know since g_temp is volatile
        if (g_temp == 0) {
            return;
        }
    }

    // Spin in an infinite loop within some nested functions to test backtrace
    intermediate1();
}
/*-----------------------------------------------------------*/


#define RRC_BACKTRACE_LIMIT 24

static void rrc_backtrace_example(void)
{
    backtrace_t trace[RRC_BACKTRACE_LIMIT];

    int count = backtrace_unwind(trace, RRC_BACKTRACE_LIMIT);

    printf("backtrace: ");
    for (int i = 0; i < count; i++) {
        printf("%08x ", (unsigned int) trace[i].address);
    }
    printf("\n");
}
/*-----------------------------------------------------------*/

void prvSetupHardware( void )
{
    /* If running on Rev A2 silicon, turn the LDO voltage up to 2.75V.  This is
     * a workaround to allow the PLL to operate reliably. */
    if( DEVICE_IS_REVA2 )
    {
        SysCtlLDOSet( SYSCTL_LDO_2_75V );
    }

    /* Set the clocking to run from the PLL at 50 MHz */
    SysCtlClockSet( SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ );

    /* Initialise the UART - QEMU usage does not seem to require this
     * initialisation. */
    SysCtlPeripheralEnable( SYSCTL_PERIPH_UART0 );
    UARTEnable( UART0_BASE );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
    static uint32_t ulTicksSinceLastDisplay = 0;
    const char * pcMessage = "PASS";
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    /* Called from every tick interrupt.  Have enough ticks passed to make it
     * time to perform our health status check again? */
    ulTicksSinceLastDisplay++;

    if( ulTicksSinceLastDisplay >= mainCHECK_DELAY )
    {
        ulTicksSinceLastDisplay = 0;

        /* Send the message to the OLED gatekeeper for display. */
        xHigherPriorityTaskWoken = pdFALSE;
        xQueueSendFromISR( xOLEDQueue, &pcMessage, &xHigherPriorityTaskWoken );
    }
}
/*-----------------------------------------------------------*/

/*
 * The display is written two by more than one task so is controlled by a
 * 'gatekeeper' task.  This is the only task that is actually permitted to
 * access the display directly.  Other tasks wanting to display a message send
 * the message to the gatekeeper.
 */
void prvOLEDTask( void * pvParameters )
{
    const char * pcMessage;
    uint32_t ulY, ulMaxY;
    static char cMessage[ mainMAX_MSG_LEN ];
    const unsigned char * pucImage;

/* Functions to access the OLED.  The one used depends on the dev kit
 * being used. */
    void ( * vOLEDInit )( uint32_t ) = NULL;
    void ( * vOLEDStringDraw )( const char *,
                                uint32_t,
                                uint32_t,
                                unsigned char ) = NULL;
    void ( * vOLEDImageDraw )( const unsigned char *,
                               uint32_t,
                               uint32_t,
                               uint32_t,
                               uint32_t ) = NULL;
    void ( * vOLEDClear )( void ) = NULL;

    /* Prevent warnings about unused parameters. */
    ( void ) pvParameters;

    /* Map the OLED access functions to the driver functions that are appropriate
     * for the evaluation kit being used. */
    configASSERT( ( HWREG( SYSCTL_DID1 ) & SYSCTL_DID1_PRTNO_MASK ) == SYSCTL_DID1_PRTNO_6965 );
    vOLEDInit = OSRAM128x64x4Init;
    vOLEDStringDraw = OSRAM128x64x4StringDraw;
    vOLEDImageDraw = OSRAM128x64x4ImageDraw;
    vOLEDClear = OSRAM128x64x4Clear;
    ulMaxY = mainMAX_ROWS_64;
    pucImage = pucBasicBitmap;
    ulY = ulMaxY;

    /* Initialise the OLED and display a startup message. */
    vOLEDInit( ulSSI_FREQUENCY );
    vOLEDStringDraw( "POWERED BY FreeRTOS", 0, 0, mainFULL_SCALE );
    vOLEDImageDraw( pucImage, 0, mainCHARACTER_HEIGHT + 1, bmpBITMAP_WIDTH, bmpBITMAP_HEIGHT );

    for( ; ; )
    {
        /* Wait for a message to arrive that requires displaying. */
        xQueueReceive( xOLEDQueue, &pcMessage, portMAX_DELAY );

        /* Write the message on the next available row. */
        ulY += mainCHARACTER_HEIGHT;

        if( ulY >= ulMaxY )
        {
            ulY = mainCHARACTER_HEIGHT;
            vOLEDClear();
            vOLEDStringDraw( pcWelcomeMessage, 0, 0, mainFULL_SCALE );
        }

        /* Display the message along with the maximum jitter time from the
         * high priority time test. */
        sprintf( cMessage, "%s %u", pcMessage, ( unsigned int ) xTaskGetTickCount() );
        vOLEDStringDraw( cMessage, 0, ulY, mainFULL_SCALE );
        printf("%s\r\n", cMessage);
    }
}
/*-----------------------------------------------------------*/

/*************************************************************************
* Please ensure to read http://www.freertos.org/portlm3sx965.html
* which provides information on configuring and running this demo for the
* various Luminary Micro EKs.
*************************************************************************/
int main( void )
{
    /* Initialise the trace recorder.  Use of the trace recorder is optional.
     * See http://www.FreeRTOS.org/trace for more information and the comments at
     * the top of this file regarding enabling trace in this demo.
     * vTraceEnable( TRC_START ); */
    prvSetupHardware();

    printf("Init complete\n");

    cm_backtrace_init("arm-cortex-qemu-demo", "1", "1");

    /* Create the queue used by the OLED task.  Messages for display on the OLED
     * are received via this queue. */
    xOLEDQueue = xQueueCreate( mainOLED_QUEUE_SIZE, sizeof( char * ) );

    /* Start the tasks defined within this file/specific to this demo. */
    xTaskCreate( prvOLEDTask, "OLED", mainOLED_TASK_STACK_SIZE, NULL, 2, &prvOLEDTaskHandle );

    /* Start a simple task to test CM backtrace */
    xTaskCreate( vDemoBacktrace, "Demo", mainOLED_TASK_STACK_SIZE, NULL, 2, &prvDemoTaskHandle );

    /* Task to test CmBacktrace ability to dump stack from other tasks */
    xTaskCreate( vInspectionTask, "Inspect", 180, NULL, 3, NULL );

    /* Uncomment the following line to configure the high frequency interrupt
     * used to measure the interrupt jitter time.
     * vSetupHighFrequencyTimer(); */

    rrc_backtrace_example();

    /* Start the scheduler. */
    vTaskStartScheduler();

    /* Will only get here if there was insufficient memory to create the idle
     * task. */
    for( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

volatile char * pcOverflowedTask = NULL; /* Prevent task name being optimised away. */
void vApplicationStackOverflowHook( TaskHandle_t pxTask,
                                    char * pcTaskName )
{
    ( void ) pxTask;
    pcOverflowedTask = pcTaskName;
    vAssertCalled( __FILE__, __LINE__ );

    for( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

void vAssertCalled( const char * pcFile,
                    uint32_t ulLine )
{
    volatile uint32_t ulSetTo1InDebuggerToExit = 0;

    taskENTER_CRITICAL();
    {
        while( ulSetTo1InDebuggerToExit == 0 )
        {
            /* Nothing to do here.  Set the loop variable to a non zero value in
             * the debugger to step out of this function to the point that caused
             * the assertion. */
            ( void ) pcFile;
            ( void ) ulLine;
        }
    }
    taskEXIT_CRITICAL();
}

/* configUSE_STATIC_ALLOCATION is set to 1, so the application must provide an
 * implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
 * used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
 * function then they must be declared static - otherwise they will be allocated on
 * the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
     * state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*-----------------------------------------------------------*/

/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
 * application must provide an implementation of vApplicationGetTimerTaskMemory()
 * to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                     StackType_t ** ppxTimerTaskStackBuffer,
                                     uint32_t * pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
 * function then they must be declared static - otherwise they will be allocated on
 * the stack and so not exists after this function exits. */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
     * task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
/*-----------------------------------------------------------*/
