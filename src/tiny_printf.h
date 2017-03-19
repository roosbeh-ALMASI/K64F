/*
 * tiny_printf.h
 *
 *  Created on: 19 Mar 2017
 *      Author: root
 */

#ifndef TINY_PRINTF_H_
#define TINY_PRINTF_H_

#include <stdarg.h>
#include <stdio.h>
#include <string.h>



void ts_itoa(char **buf, unsigned int d, int base);

/**
**---------------------------------------------------------------------------
**  Abstract: Writes arguments va to buffer buf according to format fmt
**  Returns:  Length of string
**---------------------------------------------------------------------------
*/
int ts_formatstring(char *buf, const char *fmt, va_list va);


/**
**---------------------------------------------------------------------------
**  Abstract: Calculate maximum length of the resulting string from the
**            format string and va_list va
**  Returns:  Maximum length
**---------------------------------------------------------------------------
*/
int ts_formatlength(const char *fmt, va_list va);

/**
**===========================================================================
**  Abstract: Loads data from the given locations and writes them to the
**            given character string according to the format parameter.
**  Returns:  Number of bytes written
**===========================================================================
*/
int siprintf(char *buf, const char *fmt, ...);

/**
**===========================================================================
**  Abstract: Loads data from the given locations and writes them to the
**            given file stream according to the format parameter.
**  Returns:  Number of bytes written
**===========================================================================
*/
int fiprintf(FILE * stream, const char *fmt, ...);

/**
**===========================================================================
**  Abstract: Loads data from the given locations and writes them to the
**            standard output according to the format parameter.
**  Returns:  Number of bytes written
**
**===========================================================================
*/
int iprintf(const char *fmt, ...);

/**
**===========================================================================
**  Abstract: fputs writes the string at s (but without the trailing null) to
**  the file or stream identified by fp.
**  Returns:  If successful, the result is 0; otherwise, the result is EOF.
**
**===========================================================================
*/
int fputs(const char *s, FILE *fp);

/**
**===========================================================================
**  Abstract: puts writes the string at s (followed by a newline, instead of
**  the trailing null) to the standard output stream.
**  Returns:  If successful, the result is a nonnegative integer; otherwise,
**  the result is EOF.
**
**===========================================================================
*/
int puts(const char *s);
/**
**===========================================================================
**  Abstract: Copy, starting from the memory location buf, count elements
**  (each of size size) into the file or stream identified by fp.
**  Returns:  Number of elements written
**
**===========================================================================
*/
size_t fwrite(const void * buf, size_t size, size_t count, FILE * fp);

#endif /* TINY_PRINTF_H_ */
