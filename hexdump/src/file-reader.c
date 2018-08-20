/*
 * file-reader.c
 *
 *  Created on: 29 févr. 2016
 *      Author: bernard
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
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "basedef.h"
#include "rbuffer.h"
#include "file-reader.h"

#include "private-file-header.h"

static int fr_fill_buffer(TSFileReader *fr) {
    int r = read(fr->file_handle, rb_get_buffer(fr->rbuffer), _FR_BUFFER_LEN);
    if (r < 0) {
        r = 0;
    }
    rb_reset(fr->rbuffer, r);
    return r;
}

static void fr_free(void *vfr) {
    if (vfr != NULL) {
        TSFileReader *fr = (TSFileReader *)vfr;
        rb_free(fr->rbuffer);
        free(fr);
    }
}
/**
 * memory allocation for a file-reader structure
 */
void *fr_alloc(void) {
    TSFileReader *fr =  (TSFileReader *)calloc(1, sizeof(TSFileReader));
    if (fr == NULL) {
        fprintf(stderr, "Cannot allocate memory!!!\n");
        exit (FAILURE);
    }
    fr->rbuffer = rb_allocate(_FR_BUFFER_LEN);
    return fr;
}

/**
 * position in the file stream
 */
int64_t fr_before_position(void *fr_block) {
    TSFileReader *fr = (TSFileReader *)fr_block;

    return fr->before_position;
}

int64_t fr_position(void *fr_block) {
    TSFileReader *fr = (TSFileReader *)fr_block;

    return fr->position;
}

/**
 * open a file-reader
 */
void *fr_open(const char *file_name, void *fr_block) {
    TSFileReader *fr = (TSFileReader *)fr_block;
		int file_flags = O_RDONLY;
#if defined(__WATCOMC__)
		file_flags |= O_BINARY;
#endif
    if (fr == NULL) {
        fr = fr_alloc();
    }
    fr->filename = (char *)file_name;
    fr->file_handle = open(fr->filename, file_flags);
    if (fr->file_handle == FHNotOpen) {
        fr_free (fr);
        return NULL;
    }
    return (void *)fr;
}
/**
 * read data
 */
int fr_read(void *fr_block, uint8_t *buffer, const size_t len) {
    TSFileReader *fr = (TSFileReader *)fr_block;
	int real_len;

    if (fr_isempty(fr)) {
        fr_fill_buffer(fr);
    }

    fr->before_position = fr->position;
    real_len = rb_read(fr->rbuffer, buffer, len);
    if (real_len > 0) {
		fr->position += (int64_t)real_len;
	}
    return real_len;
}
/**
 * close a file-reader
 */
void fr_close(void *fr_block) {
    TSFileReader *fr = (TSFileReader *)fr_block;
    if (fr != NULL) {
        if (fr->file_handle != FHNotOpen) {
            close(fr->file_handle);
        }
        fr_free(fr_block);
    }
}

