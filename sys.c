#include <sys/stat.h>

extern int _end;

int _close(int file) {
  return -1;
}

int _fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;

  return 0;
}

int _isatty(int file) {
  return 1;
}

int _lseek(int file, int ptr, int dir) {
  return 0;
}

void _exit(int status) {
  __asm("BKPT #0");
}

void _kill(int pid, int sig) {
  return;
}

int _getpid(void) {
  return -1;
}

//int _write (int file, char * ptr, int len) {
//  int written = 0;
//
//  if ((file != 1) && (file != 2) && (file != 3)) {
//    return -1;
//  }
//
//  for (; len != 0; --len) {
//    if (usart_serial_putchar(&stdio_uart_module, (uint8_t)*ptr++)) {
//      return -1;
//    }
//    ++written;
//  }
//  return written;
//}

int _read (int file, char * ptr, int len) {
  int read = 0;

  if (file != 0) {
    return -1;
  }

  for (; len > 0; --len) {
//    usart_serial_getchar(&stdio_uart_module, (uint8_t *)ptr++);
    read++;
  }
  return read;
}
