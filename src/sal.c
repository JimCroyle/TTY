/* sal.c - System Abstraction Layer
 *
 * provide abstraction layer for OS related functionality
 *
 * -------------- SAL INIT --------------------
 * sal_Init() ~ configure abstracton layer
 *
 * ------------- MEMORY API -------------------
 * sal_Malloc() ~ abstraction for malloc()
 * sal_Free() ~ absraction for free()
 *
 * --------------- TIME API -------------------
 * sal_GetTime() ~ sample time for measure elapsed
 * sal_ElapstedTime() ~ calculate elapsed time 
 * sal_TimeToUsec() ~ convert time to # microsec
 * sal_TimeToMsec() ~ convert time to # millisec
 *
 */
#include "sal.h"

static bool sal_initialized = false;
static uint64_t time_usec = 0uLL;
static void sal_UpdateUsecElapsed(void);

static sal_Time_t begin_time;

/* ------------------------------------------------- */

/*** sal_Init() ~ initialize System Abstraction Layer
*/
void sal_Init (void)
{
    begin_time = clock();
    sal_initialized = true;
}

/*** sal_Malloc() ~ call stdlib malloc()
*/
void * sal_Malloc ( int num_bytes )
{
    DBG_Assert(sal_initialized);
    return malloc(num_bytes);
}

/*** sal_Free() ~ call stdlib free()
*/
void sal_Free ( void *ptr )
{
    DBG_Assert(sal_initialized);
    free(ptr);
}

/*** sal_GetTimeUsec() ~ read elapsed usec since sal_Init() called
*/
sal_Time_t sal_GetTime (void)
{
    DBG_Assert(sal_initialized);
    return clock();
}

/*** sal_ElapsedUsec() ~ calculate elapsed usec (acct for rollover)
*/
sal_Time_t sal_ElapsedTime (sal_Time_t time)
{
    DBG_Assert(sal_initialized);
    return (double) (clock() - time);
}

/*** sal_TimeToUsec() ~ convert time value to microseconds
*/
uint64_t sal_TimeToUsec (sal_Time_t time)
{
    double usec = (double) time / (double)(CLOCKS_PER_SEC / USEC_PER_SEC);
    return (uint64_t) usec;
}

/*** sal_TimeToMsec() ~ convert time to milliseconds
*/
uint64_t sal_TimeToMsec (sal_Time_t time)
{
    double msec = (double) time / (double)(CLOCKS_PER_SEC / MSEC_PER_SEC);
    return (uint64_t) msec;    
}

/* EOF */