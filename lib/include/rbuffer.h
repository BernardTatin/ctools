/* 
 * File:   rbuffer.h
 * Author: bernard
 * 
 * Created on 25 avril 2016, 00:36
 */
/*
    The MIT License (MIT)

    Copyright (c) {YEAR} Bernard TATIN <bernard dot tatin at outlook dot org>

    Permission is hereby grante2016d, free of charge, to any person obtaining a copy
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

#ifndef RBUFFER_H
#define	RBUFFER_H

typedef struct _RBuffer {
	uint8_t *buffer;
	int ptr_out;
	int count;
	int size;
} TSRBuffer;

void *rb_allocate(const int buffer_size);
void rb_free(void *rb);

static inline void *rb_get_buffer(void *vrb) {
	return ((TSRBuffer *)vrb)->buffer;
}

static inline void rb_reset(void *vrb, const int count) {
	TSRBuffer *rb = (TSRBuffer *)vrb;

	rb->ptr_out = 0;
	rb->count = count;
}
#endif	/* RBUFFER_H */

