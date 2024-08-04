#include <string.h>

// Avoid fortify source macros affecting implementation below
#ifdef strcpy
#undef strcpy
#endif

char *__stpcpy(char *restrict dest, const char *restrict src);

char *strcpy(char *restrict dest, const char *restrict src)
{
	__stpcpy(dest, src);
	return dest;
}
