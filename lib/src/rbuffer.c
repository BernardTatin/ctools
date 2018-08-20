/*
 * File:   rbuffer.c
 * Author: bernard
 *
 * Created on 25 avril 2016, 00:45
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

#include "compat.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "rbuffer.h"
#include "basedef.h"

int rb_read(void *vrb, void *buffer, const size_t len) {
    TSRBuffer *rbuffer = (TSRBuffer *)vrb;
    size_t real_len = min(len, (size_t)(rbuffer->count - rbuffer->ptr_out));

    if (real_len != 0) {
        memmove(buffer, rbuffer->buffer + rbuffer->ptr_out, real_len);
        rbuffer->ptr_out += real_len;
    }
    return real_len;
}

void *rb_allocate(const size_t buffer_size) {
    TSRBuffer *rb = (TSRBuffer *) calloc(1, sizeof (TSRBuffer));

    if (rb == NULL) {
        // fprintf(stderr, "Cannot allocate memory !!!\n");
        exit(FAILURE);
    }
    rb->size = buffer_size;
    rb->buffer = (uint8_t *) calloc(1, buffer_size);
    if (rb->buffer == NULL) {
        free(rb);
        // fprintf(stderr, "Cannot allocate memory !!!\n");
        exit(FAILURE);
    }
    return (void *) rb;
}

void rb_free(void *vrb) {
    if (vrb != NULL) {
        TSRBuffer *rb = (TSRBuffer *) vrb;

        if (rb->buffer != NULL) {
            free(rb->buffer);
            rb->buffer = NULL;
        }
        free(rb);
    }
}
