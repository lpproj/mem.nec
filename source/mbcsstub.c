/*
mbcsstub.c (and mbcsstub.h)

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*/


#include <dos.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mbcsstub.h"


static unsigned char dbcfield[16];
static unsigned char my_mb_cur_max = 0;

static unsigned char dbcfield_default[] = { 0, 0 };
static unsigned char dbcfield_cp932[] = { 0x81, 0x9f, 0xe0, 0xfc, 0, 0 };

static char my_upr(char c)
{
	if (c >= 'a' && c <= 'z') return c - 'a' + 'A';
	return c;
}

static unsigned char setup_dbcfield(void)
{
	unsigned char rc = 1;
	unsigned char far *p = dbcfield_default;
	char *lang = getenv("LANG");

	if (lang && my_upr(*lang)=='J' && my_upr(lang[1])=='A') {
		p = dbcfield_cp932;
	}
	else {
		union REGS r;
		struct SREGS sr;
		r.x.si = sr.ds = 0;
		r.x.ax = 0x6300;
		intdosx(&r, &r, &sr);
		if (r.x.si || sr.ds) {
			p = MK_FP(sr.ds, r.x.si);
			/* workaround for some clone DOSes (which returns wrong DBCStbl address) */
			if (*p > 0 && *p <= 6 && p[1] == 0) p += 2;
		}
	}
	if (*p != 0) {
		unsigned i;
		rc = 2;		/* guess DBCS environment */
		for(i=0; i < sizeof(dbcfield); i += 2) {
			dbcfield[i] = p[i];
			dbcfield[i+1] = p[i+1];
			if (dbcfield[i] == 0) break;
		}
	}
	else {
		*(unsigned *)&(dbcfield[0]) = 0;
	}
	return rc;
}

#define check_dbcfield() { if (!my_mb_cur_max) my_mb_cur_max = setup_dbcfield(); }

int
my_mb_curmax(void)
{
	check_dbcfield();
	return my_mb_cur_max;
}

int
my_mblen_loose(const void *s)
{
	int rc = 1;
	check_dbcfield();
	if (my_mb_cur_max > 1) {
		unsigned char c = *(const unsigned char *)s;
		unsigned n;
		for(n=0; n<sizeof(dbcfield); n += 2) {
			if (dbcfield[n] == 0) break;
			if (c >= dbcfield[n] && c <= dbcfield[n+1]) {
				if (((unsigned char *)s)[1] >= 0x20) rc = 2;	/* avoid buffer overrun */
				break;
			}
		}
	}
	return rc;
}

int
my_mblen(const void *p, int mbmax)
{
	if (mbmax > 1) return my_mblen_loose(p);
	return 1;
}


unsigned char *
my_mbschr(const void *p, unsigned c)
{
	unsigned char *r = NULL;
	const unsigned char *s = p;

	while(1) {
		if (*s == (unsigned char)c) {
			r = (unsigned char *)s;
			break;
		}
		if (*s == '\0') break;
		s += my_mblen_loose(s);
	}
	return r;
}

#if 0		/* not used in kitten.c */
unsigned char *
my_mbsrchr(const void *p, unsigned c)
{
	unsigned char *r = NULL;
	const unsigned char *s = p;

	while(1) {
		if (*s == (unsigned char)c) {
			r = (unsigned char *)s;
		}
		if (*s == '\0') break;
		s += my_mblen_loose(s);
	}
	return r;
}
#endif

