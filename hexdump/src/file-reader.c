/*
 * file-reader.c
 *
 *  Created on: 29 févr. 2016
 *      Author: bernard
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "basedef.h"
#include "file-reader.h"

#include "private-file-header.h"

static int fr_fill_buffer(TSFileReader *fr) {
	int r = read(fr->file_handle, fr->buffer, _FR_BUFFER_LEN);
	if (r < 0) {
		r = 0;
	}
	fr->ptr_out = 0;
	fr->count = r;
	return r;
}

static void fr_free(void *vfr) {
	if (vfr != NULL) {
		TSFileReader *fr = (TSFileReader *)vfr;
		if (fr->buffer != NULL) {
			free(fr->buffer);
			fr->buffer = NULL;
		}
		free(fr);
	}
}
/**
 * memory allocation for a file-reader structure
 */
static void *fr_alloc(void) {
	TSFileReader *fr =  (TSFileReader *)calloc(1, sizeof(TSFileReader));
	if (fr == NULL) {
		fprintf(stderr, "Cannot allocate memory!!!\n");
		exit (FAILURE);
	}
	fr->buffer = (uint8_t *)calloc(_FR_BUFFER_LEN, sizeof(uint8_t));
	if (fr->buffer == NULL) {
		fr_free(fr);
		fprintf(stderr, "Cannot allocate memory!!!\n");
		exit (FAILURE);
	}
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
	if (fr == NULL) {
		fr = fr_alloc();
	}
	fr->filename = (char *)file_name;
	fr->file_handle = open(fr->filename, O_RDONLY);
	if (fr->file_handle == FHNotOpen) {
		fr_free (fr);
		return NULL;
	}
	return (void *)fr;
}
/**
 * read data
 */
int fr_read(void *fr_block, uint8_t *buffer, const int len) {
	TSFileReader *fr = (TSFileReader *)fr_block;
	if (fr_isempty(fr)) {
		fr_fill_buffer(fr);
	}

	int real_len = min(len, fr->count - fr->ptr_out);
	if (real_len < 0) {
		real_len = 0;
	} else {
		memmove(buffer, fr->buffer + fr->ptr_out, real_len);
		fr->ptr_out += real_len;
	}
	fr->before_position = fr->position;
	fr->position += (int64_t)real_len;
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

