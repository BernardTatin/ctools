/*
 * _stdbool.h
 *
 *  Created on: 5 sept. 2015
 *      Author: bernard
 */

#ifndef INCLUDE__COMPAT__STDBOOL_H_
#define INCLUDE__COMPAT__STDBOOL_H_

#if defined(true)
#undef true

#if defined(false)
#undef false
#endif

typedef enum {
        false = 0,
        true = 1
} bool;
#endif

#endif /* INCLUDE__COMPAT__STDBOOL_H_ */
