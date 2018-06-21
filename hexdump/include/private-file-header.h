/*
 * private-file-header.h
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


#ifndef PRIVATE_FILE_HEADER_H_
#define PRIVATE_FILE_HEADER_H_

#include "rbuffer.h"


#define _FR_BUFFER_LEN		(1024 * 4)

typedef int TDFileHandle;
typedef enum { FHNotOpen = -1 } TEFileHValues;

typedef struct _FileReader {
	char *filename;
	int64_t position;
	int64_t before_position;
	TDFileHandle file_handle;
	bool eof;

	TSRBuffer *rbuffer;
} TSFileReader;

static INLINE bool fr_isopen(TSFileReader *fr) {
	return (fr != NULL) && (fr->file_handle != FHNotOpen);
}

static INLINE bool fr_iseof(TSFileReader *fr) {
	return fr->eof;
}

static INLINE bool fr_isempty(TSFileReader *fr) {
	return rb_isempty(fr->rbuffer);
}
#endif /* PRIVATE_FILE_HEADER_H_ */
