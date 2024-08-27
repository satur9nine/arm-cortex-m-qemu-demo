#include <stdio.h>
#include <sys/stat.h>

#include "cmsis_impl.h"
#include "accoutrements.h"


char *__env[1] = { 0 };
char **environ = __env;

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
  __disable_irq();
  fault_printf("Exit with status %d\n", status);
  force_crash(CRASH_TYPE_EXIT);
}

void _kill(int pid, int sig) {
  (void) pid;
  __disable_irq();
  fault_printf("Kill with signal %d\n", sig);
  force_crash(CRASH_TYPE_KILL);
}

int _getpid(void) {
  return 1;
}
