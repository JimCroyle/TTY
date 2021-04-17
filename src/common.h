/* common.h
 *
 * this file contains various helper macros and definitions common to all files
 * common.h is intended to be included in every C source file.
 */
#ifndef __COMMON__
#define __COMMON__

#include "my_assert.h"
#include "result.h"

typedef unsigned char Byte_t;

/* common helper macros
*/
#define NUM_ELEMENTS(a) (sizeof(a[0]) ? sizeof(a) / sizeof(a[0]) : -1)

/* self-documenting unit specifiers
*/
#define MSEC(msec)  (msec)
#define USEC(usec)  (usec)
#define SEC(sec)    (sec)

#define MSEC_PER_SEC  (1000)
#define USEC_PER_SEC  (MSEC_PER_SEC * 1000)

#endif /* __COMMON__ */
