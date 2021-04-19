/* main.c ~ test program for TTY lib
 * 
 * provides functionality for providing automated unit testing followed by interfactive
 * testing.  A basic set of commands are provided to test/demo various MyTty features.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "common.h"
#include "tty_session.h";

static int RunUnitTests (void);
static int RunInteractive (void);

/*** main test program entry point
*/
int main (int argc, char *argv[])
{
    #ifdef TEST_ASSERT
    DBG_ASSERT(true); // SHOULD NOT FIRE  
    DBG_ASSERT_MSG(false, "this is only a test");
    DBG_ASSERT(false);  
    #endif

    printf("\nTTY Test Program\n\n");
    RunUnitTests();
    RunInteractive();
}

/*** 
*/
static int RunUnitTests (void)
{
    printf("Running Unit Tests -- not yet implemented\n");
}

/*** 
*/
static int RunInteractive (void)
{
    printf("Running Interactive Session -- not yet implemented\n");
}

/* EOF */