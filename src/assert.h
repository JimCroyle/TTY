/* assert.h
 */
#ifndef __ASSERT__
#define __ASSERT__

/* uncomment the following line to test the assert logic
*/
#define TEST_ASSERT

/* assert interface definition/binding
*/
#if 1
extern void dbg_assert(const bool cond, int line_num, char *filename);
#define DBG_ASSERT_HANDLER  dbg_assert
#endif 

#ifdef  DBG_ASSERT_HANDLER
#define DBG_ASSERT(cond)  ((cond) ? : DBG_ASSERT_HANDLER(__FILE__,__LINE__))
#else
#define DBG_ASSERT(cond)
#endif

#endif /*  __ASSERT__ */

/* EOF */