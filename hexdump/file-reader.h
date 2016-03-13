/*
 * file-reader.h
 *
 *  Created on: 29 févr. 2016
 *      Author: bernard
 */

#ifndef FILE_READER_H_
#define FILE_READER_H_


/**
 * memory allocation for a file-reader structure
 */
void *fr_alloc(void);
/**
 * open a file-reader
 */
void *fr_open(const char *file_name, void *fr_block);
/**
 * read data
 */
int fr_read(void *fr_block, uint8_t *buffer, const int len);
/**
 * close a file-reader
 */
void fr_close(void *fr_block);

#endif /* FILE_READER_H_ */
