/* tty_command.c
 *
 * terminal command framework
 *
 */
#include "tty_command.h"

/*** cmd_RunPrompt() ~ display prompt and reset command input state
*/
Result_t cmd_RunPrompt ( TtySession *tty )
{
    Result_t result = SUCCESS;
    char str[256];

    sprintf(str, "tty%02d-%s-%05d> ", tty->login_ctr, 
                                      tty->username, 
                                      tty->cmd_ctr);
    return result;
}

/*** cmd_RunInput() ~ run command input state
*/
Result_t cmd_RunInput ( TtySession *tty )
{
    Result_t result = SUCCESS;
    return result;
}

/*** cmd_RunExecute() ~ execute command string 
*/
Result_t cmd_RunExecute ( TtySession *tty )
{
    Result_t result = SUCCESS;
    return result;
}

/*** cmd_RunRepeat() ~ repeat last command until key-pressed
*/
Result_t cmd_RunRepeat ( TtySession *tty )
{
    Result_t result = SUCCESS;
    return result;
}
 /* EOF */