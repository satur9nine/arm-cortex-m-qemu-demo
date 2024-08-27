#include <stdio.h>

#include "hw_memmap.h"
#include "hw_sysctl.h"
#include "hw_types.h"
#include "hw_uart.h"
#include "sysctl.h"
#include "uart.h"


int _write(int handle, char *data, int size)
{
    int count;

    (void) handle;

    for(count = 0; count < size; count++)
    {
        char c = data[count];
        if (c == '\n') {
            UARTCharPut( UART0_BASE, '\r');
        }
        UARTCharPut( UART0_BASE, c);
    }

    return count;
}

int _read(int file, char * ptr, int len)
{
  int read = 0;

  if (file != 0) {
    return -1;
  }

  for (; len > 0; --len) {
    ptr[read] = UARTCharGet( UART0_BASE );
    read++;
  }
  return read;
}
