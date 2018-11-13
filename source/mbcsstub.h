/*
    This file is a part of mbcsstub(.c)
*/

#ifndef MY_MBCSSTUB_H
#define MY_MBCSSTUB_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MBCS
typedef unsigned char  MYMBCS_CHAR;
#else
typedef char  MYMBCS_CHAR;
#endif


int my_mb_curmax(void);
int my_mblen_loose(const void *);
int my_mblen(const void *, int);

/* similar as Microsoft's functions */
MYMBCS_CHAR *  my_mbschr(const void *, unsigned);
MYMBCS_CHAR *  my_mbsrchr(const void *, unsigned);
MYMBCS_CHAR *  my_mbsupr(const void *);
MYMBCS_CHAR *  my_mblwr(const void *);

#ifdef __cplusplus
}
#endif

#endif /* MY_MBCSSTUB_H */

