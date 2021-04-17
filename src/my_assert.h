/* my_assert.h
 */
#ifndef __MY_ASSERT__
#define __MY_ASSERT__

/* uncomment the following line to test the assert logic
*/
#define TEST_ASSERT

/* assert interface definition/binding
*/
#if 1
extern void dbg_assert(int line_num, char *filename);
#define DBG_ASSERT(cond)  if (cond) { dbg_assert(__LINE__, __FILE__); }
#else
#define DBG_ASSERT(cond)
#endif 

#endif /*  __MY_ASSERT__ */
