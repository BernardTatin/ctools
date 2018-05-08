/**
 * compat.h
 */

#if !defined(__compat_h__)
#define __compat_h__

  #include <stdlib.h>
  #include <stdarg.h>
  #include <string.h>

  #if defined(__WATCOMC__)
    #define INLINE __inline
    #define _Noreturn
    #include <stdbool.h>
    #include <sys/types.h>
  #elif defined(_MSC_VER)
    #define INLINE
    #define _Noreturn
    #include "_compat/_stdbool.h"
    #include "_compat/_stdint.h"
  #elif defined(__TURBOC__)
    #define _Noreturn
    #define INLINE
    #include "_compat/_stdbool.h"
    #include "_compat/_stdint.h"
  #else
    #define INLINE inline
    #include <stdbool.h>
    #include <stdint.h>
  #endif

#endif
