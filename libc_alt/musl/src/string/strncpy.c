#include <string.h>

// Avoid fortify source macros affecting implementation below
#ifdef strncpy
#undef strncpy
#endif

char *__stpncpy(char *restrict d, const char *restrict s, size_t n);

char *strncpy(char *restrict d, const char *restrict s, size_t n)
{
	__stpncpy(d, s, n);
	return d;
}
