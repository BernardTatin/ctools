/* 
 * File:   basedef.h
 * Author: Bernard TATIN <bernard dot tatin at outlook dot org>
 *
 * Created on 22 février 2016, 23:55
 */

#ifndef BASEDEF_H
#define	BASEDEF_H

#ifdef	__cplusplus
extern "C" {
#endif


#if !defined(SUCCESS)
#define SUCCESS 0
#endif

#if !defined(FAILURE)
#define FAILURE 1
#endif

static inline int min(int a, int b) {
	if (a < b) {
		return a;
	} else {
		return b;
	}
}

#ifdef	__cplusplus
}
#endif

#endif	/* BASEDEF_H */

