/* tty_command.h
 *
 * provides command architecture - application defines command function table
 */
#ifndef __TTY_COMMAND__
#define __TTY_COMMAND__

#include "common.h"

/*** command state 
*/
typedef enum _CmdState_e
{
    CS_PROMPT=0,    /* prompt for command */
    CS_INPUT,       /* accept input for command */
    CS_EXECUTE,     /* execute command input */
    CS_REPEAT,      /* auto repeat command processing */

}   CmdState_t;


/*** terminal session API
*/
Result_t cmd_RunPrompt   (TtySession_t *tty);
Result_t cmd_RunInput    (TtySession_t *tty);
Result_t cmd_RunExecute  (TtySession_t *tty);
Result_t cmd_RunRepeat   (TtySession_t *tty);


#endif /* __TTY_COMMAND__ */
