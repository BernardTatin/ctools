/* 
 * File:   hexops.h
 * Author: bernard
 *
 * Created on 23 avril 2016, 21:18
 */
/*
    The MIT License (MIT)

    Copyright (c) 2016 Bernard TATIN <bernard dot tatin at outlook dot org>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

 */


#ifndef HEXOPS_H
#define	HEXOPS_H

extern char *hex_chars;

static INLINE char normalize_byte(uint8_t c) {
	if (c < 32 || c > 126) {
		return '.';
	} else {
		return (char)c;
	}
}


static INLINE char *put_hex_byte(char *dst, uint8_t b) {
	uint8_t hbyte = (b >> 4) & 0x0f;
	uint8_t lbyte = b & 0x0f;
	*(dst++) = *(hex_chars + hbyte);
	*(dst++) = *(hex_chars + lbyte);
	*(dst++) = ' ';
	return dst;
}

static INLINE char *put3spaces(char *dst) {
	*(dst++) = ' ';
	*(dst++) = ' ';
	*(dst++) = ' ';
	return dst;
}
#endif	/* HEXOPS_H */

