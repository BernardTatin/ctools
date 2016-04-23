/* 
 * File:   hexops.h
 * Author: bernard
 *
 * Created on 23 avril 2016, 21:18
 */

#ifndef HEXOPS_H
#define	HEXOPS_H

static inline char normalize_byte(uint8_t c) {
	if (c < 32 || c > 126) {
		return '.';
	} else {
		return (char)c;
	}
}
#endif	/* HEXOPS_H */

