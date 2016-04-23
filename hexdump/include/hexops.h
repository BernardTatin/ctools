/* 
 * File:   hexops.h
 * Author: bernard
 *
 * Created on 23 avril 2016, 21:18
 */

#ifndef HEXOPS_H
#define	HEXOPS_H

extern char *hex_chars;

static inline char normalize_byte(uint8_t c) {
	if (c < 32 || c > 126) {
		return '.';
	} else {
		return (char)c;
	}
}


static inline char *put_hex_byte(char *dst, uint8_t b) {
	uint8_t hbyte = (b >> 4) & 0x0f;
	uint8_t lbyte = b & 0x0f;
	*(dst++) = *(hex_chars + hbyte);
	*(dst++) = *(hex_chars + lbyte);
	*(dst++) = ' ';
	return dst;
}

static inline char *put3spaces(char *dst) {
	*(dst++) = ' ';
	*(dst++) = ' ';
	*(dst++) = ' ';
	return dst;
}
#endif	/* HEXOPS_H */

