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
  // #include "_compat/_stdint.h"
  /* __inline */
#elif defined(_MSC_VER)
  #define _Noreturn
  #include "_compat/_stdbool.h"
  #include "_compat/_stdint.h"
  #define INLINE
#elif defined(__TURBOC__)
  #define _Noreturn
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
