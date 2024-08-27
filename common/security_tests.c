#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmsis_impl.h"


// When stack protector is enabled the compiler should detect stack buffer
// overflow and call __stack_chk_fail
int test_stack_buffer_overflow(unsigned int number)
{
    uint8_t buf[1];
    for (unsigned int i = 0; i < number; i++)
    {
        buf[i] = number + i;
    }

    return buf[number - 1];
}

typedef struct {
    uint8_t x;
    uint8_t y;
} point_t;

static point_t g_point;

// This should be caught by the compiler at runtime when FORTIFY_SOURCE 2 or
// higher enabled since the memset parameter is smaller than 10 bytes
void test_fortify_source_level2(void)
{
    memset(&g_point, 0x99, 10);
}

static char *g_b;
static char g_buf1[21];

char *do_set(bool cond)
{
    char *buf = g_buf1;
    if (cond)
        buf = malloc(42);

    memset(buf, 0, 22);
    return buf;
}

// This should be caught by the compiler at runtime when FORTIFY_SOURCE 3 or
// higher enabled
void test_fortify_source_level3(void)
{
    g_b = do_set(false);
}
