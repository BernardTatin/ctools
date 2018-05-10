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
    typedef enum {
            false = 0,
            true = 1
    } bool;
    #ifndef _EXACT_WIDTH_INTS
      #define _EXACT_WIDTH_INTS
      typedef signed char int8_t;
      typedef unsigned char uint8_t;
      typedef short int16_t;
      typedef unsigned short uint16_t;
      typedef int int32_t;
      typedef unsigned int uint32_t;
      typedef long long int64_t;
      typedef unsigned long long uint64_t;
    #endif /* _EXACT_WIDTH_INTS */
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
