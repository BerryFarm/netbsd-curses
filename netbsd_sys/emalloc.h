#ifndef EMALLOC_H
#define EMALLOC_H

/* replacement functions for emalloc() and friends used in netbsd code */

#undef _GNU_SOURCE
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/*Hck BBOS10*/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int vasprintf(char **s, const char *fmt, va_list ap)
{
	va_list ap2;
	va_copy(ap2, ap);
	int l = vsnprintf(0, 0, fmt, ap2);
	va_end(ap2);

	if (l<0 || !(*s=malloc(l+1U))) return -1;
	return vsnprintf(*s, l+1U, fmt, ap);
}
/*Hck BBOS10*/

static void mallerr(void) {
	printf(2, "error: out of memory\n");
	abort();
}
static inline void* emalloc(size_t x) {
	void *p=malloc(x);
	if(!p) mallerr();
	return p;
}
static inline void* ecalloc(size_t x, size_t y) {
	void *p=calloc(x, y);
	if(!p) mallerr();
	return p;
}
static inline void* erealloc(void *x, size_t y) {
	void *p=realloc(x, y);
	if(!p) mallerr();
	return p;
}
static inline char* estrdup(const char* x) {
	char *p = strdup(x);
	if(!p) mallerr();
	return p;
}
static int easprintf(char **s, const char *fmt, ...) {
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vasprintf(s, fmt, ap);
	va_end(ap);
	if(ret == -1) mallerr();
	return ret;
}

#endif

