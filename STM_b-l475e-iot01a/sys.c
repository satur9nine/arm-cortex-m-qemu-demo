#include <stdio.h>
#include <sys/stat.h>

#include "main.h"
#include "accoutrements.h"

char *__env[1] = { 0 };
char **environ = __env;

int __io_putchar(int ch)
{
  if (ch == '\n') {
    int r = '\r';
    if (HAL_OK != HAL_UART_Transmit(&huart1, (uint8_t *) &r, 1, 3000)) {
      force_crash(CRASH_TYPE_HAL_ERROR);
    }
  }
  if (HAL_OK != HAL_UART_Transmit(&huart1, (uint8_t *) &ch, 1, 3000)) {
    force_crash(CRASH_TYPE_HAL_ERROR);
  }

  return ch;
}

int __io_getchar(void)
{
  uint8_t ch = 0;
  if (HAL_OK != HAL_UART_Receive(&huart1, (uint8_t *) &ch, 1, 3000)) {
    force_crash(CRASH_TYPE_HAL_ERROR);
  }
  return ch;
}

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

int _write(int file, char *ptr, int len)
{
  (void)file;
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    __io_putchar(*ptr++);
  }
  return len;
}

int _read(int file, char *ptr, int len)
{
  (void)file;
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    *ptr++ = __io_getchar();
  }

  return len;
}
