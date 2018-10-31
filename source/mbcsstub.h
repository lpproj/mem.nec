/*
    This file is a part of mbcsstub(.c)
*/

#ifndef MY_MBCSSTUB_H
#define MY_MBCSSTUB_H

#ifdef __cplusplus
extern "C" {
#endif

int my_mb_curmax(void);
int my_mblen_loose(const void *);
int my_mblen(const void *, int);

/* similar as Microsoft's functions */
unsigned char *  my_mbschr(const void *, unsigned);
unsigned char *  my_mbsrchr(const void *, unsigned);
unsigned char *  my_mbsupr(const void *);
unsigned char *  my_mblwr(const void *);

#ifdef __cplusplus
}
#endif

#endif

