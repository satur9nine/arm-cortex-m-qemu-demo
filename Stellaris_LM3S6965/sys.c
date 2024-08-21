#include <stdio.h>
#include <sys/stat.h>

#include "hw_memmap.h"
#include "hw_sysctl.h"
#include "hw_types.h"
#include "hw_uart.h"
#include "sysctl.h"
#include "uart.h"

int _close(int file) {
  (void) file;
  return -1;
}

int _fstat(int file, struct stat *st) {
  (void) file;
  st->st_mode = S_IFCHR;
  return 0;
}

int _isatty(int file) {
  (void) file;
  return 1;
}

int _lseek(int file, int ptr, int dir) {
  (void) file;
  (void) ptr;
  (void) dir;
  return 0;
}

void _exit(int status) {
  (void) status;
  __asm("BKPT #0");
  while (1);
}

void _kill(int pid, int sig) {
  (void) pid;
  (void) sig;
}

int _getpid(void) {
  return -1;
}

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

int _read (int file, char * ptr, int len)
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
