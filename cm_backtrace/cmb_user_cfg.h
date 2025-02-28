#ifndef _CMB_USER_CFG_H_
#define _CMB_USER_CFG_H_

#include "accoutrements.h"

#define cmb_println(...) do { fault_printf(__VA_ARGS__); fault_printf("\r\n"); } while (0)

/* enable OS platform */
#define CMB_USING_OS_PLATFORM
/* OS platform type, must config when CMB_USING_OS_PLATFORM is enable */
#define CMB_OS_PLATFORM_TYPE CMB_OS_PLATFORM_FREERTOS
/* cpu platform type, must config by user */
#define CMB_CPU_PLATFORM_TYPE CMB_CPU_ARM_CORTEX_M3
/* enable dump stack information */
/* #define CMB_USING_DUMP_STACK_INFO */
/* language of print information */
/* #define CMB_PRINT_LANGUAGE             CMB_PRINT_LANGUAGE_ENGLISH(default) or CMB_PRINT_LANGUAGE_CHINESE or CMB_PRINT_LANGUAGE_CHINESE_UTF8 */

#define CMB_CALL_STACK_MAX_DEPTH 12

#endif /* _CMB_USER_CFG_H_ */
