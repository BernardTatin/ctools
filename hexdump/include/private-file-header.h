/*
 * private-file-header.h
 *
 *  Created on: 29 févr. 2016
 *      Author: bernard
 */

#ifndef PRIVATE_FILE_HEADER_H_
#define PRIVATE_FILE_HEADER_H_

#define _FR_BUFFER_LEN		(1024 * 4)

typedef int TDFileHandle;
typedef enum { FHNotOpen = -1 } TEFileHValues;

typedef struct _FileReader {
	char *filename;
	uint8_t *buffer;
	int64_t position;
	int64_t before_position;
	int ptr_out;
	int count;
	TDFileHandle file_handle;
	bool eof;
} TSFileReader;

static inline bool fr_isopen(TSFileReader *fr) {
	return (fr != NULL) && (fr->file_handle != FHNotOpen);
}

static inline bool fr_iseof(TSFileReader *fr) {
	return fr->eof;
}

static inline bool fr_isempty(TSFileReader *fr) {
	int count = fr->count;
	return (count == 0) || (fr->ptr_out+1 >= count);
}
#endif /* PRIVATE_FILE_HEADER_H_ */
