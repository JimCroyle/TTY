/* result.h
 *
 * this file contains result codes as enums
 */
#ifndef __RESULT__
#define __RESULT__

#define SUCCESS     ( RESULT_OK )
#define NO_ERROR    ( RESULT_OK )

typedef enum _Result_e
{
    RESULT_OK       = 0,
    ERR_BAD_VALUE   = 0x0001,
    ERR_NULL_ARG    = 0x0002,
    ERR_ALLOC_FAIL  = 0x0003,
    ERR_UNDEFINED   = 0xFFFF

}   Result_t;

#endif  /* __RESULT__ */
