/* sal.h - System Abstraction Layer API
 *
 */
#ifndef __SAL__
#define __SAL__

#include <common.h>
#include <ctypes.h>
#include <time.h>

/*** SAL initialization - must be called prior to first API call
*/
void sal_Init (void);

typedef clock_t sal_Time_t;

/*** memory allocation API
*/
void *sal_Malloc ( int num_bytes );
void  sal_Free   ( void *ptr );

/* time based API
*/
sal_Time_t sal_GetTime (void);
sal_Time_t sal_ElapsedTime (sal_Time_t time);

uint64_t sal_TimeToUsec (sal_Time_t time);
uint64_t sal_TimeToMsec (sal_Time_t time);

static inline uint32_t sal_ElapsedMsec (sal_Time_t time)
{
    return (uint32_t) sal_TimeToMsec(sal_ElapsedTime(time));
}

static inline uint32_t sal_ElapsedUsec (sal_Time_t time)
{
    return (uint32_t) sal_TimeToUsec(sal_ElapsedTime(time));
}

#endif  /* __SAL__ */

/* EOF */