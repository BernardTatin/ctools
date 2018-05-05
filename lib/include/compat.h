/**
 * compat.h
 */

#if !defined(__compat_h__)
#define __compat_h__

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#if defined(__WATCOMC__)
  #include <stdbool.h>
  #include "_compat/_stdint.h"
  #define INLINE 
  // __inline
#elif defined(_MSC_VER)
  #include "_compat/_stdbool.h"
  #include "_compat/_stdint.h"
  #define INLINE 
#elif defined(__TURBOC__)
  #include "_compat/_stdbool.h"
  #include "_compat/_stdint.h"
  #define INLINE
#else
  #include <stdbool.h>
  #include <stdint.h>
  #define INLINE inline
#endif


#include <string.h>

#endif
