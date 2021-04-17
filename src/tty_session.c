/* tty_session.c
 *
 * terminal session control interface; contains main state machine for
 * processing character based streaming of commands via a serial device
 *
 * MyTty Assumptions:
 * -------------------
 * 0. multiple simultaneous terminal sessions is supported
 * 1. characters are processwed one at a time
 * 2. line editing is supported including left/right arrows
 * 3. up and down arrows support command history
 * 4. 
 */
#include "tty_session.h"

static Result_t RunLogin    (TtySession_t *tty);
static Result_t RunUser     (TtySession_t *tty);
static Result_t RunPassword (TtySession_t *tty);
static Result_t RunCommand  (TtySession_t *tty);
static Result_t RunRepeat   (TtySession_t *tty);
static Result_t RunLocked   (TtySession_t *tty);

/*** tty_NewSession() ~ allocate a new session context and init to cfg settings
*/
Result_t tty_NewSession ( TtySession **tty, TtyConfig_t *cfg )
{
    Result_t result = SUCCESS;
    TtySession_t *new_tty = osal_Malloc(sizeof(TtySession));
    if ( NULL == new_tty )
        result = ERR_ALLOC_FAIL;
    else
    {
        *tty = new_tty;
        memcpy(&tty->cfg, cfg, sizeof(TtyConfig_t));
    }

    return result;
}

/*** tty_RunSession() ~ update tty session, run state machine
*/
Result_t tty_RunSession ( TtySession_t *tty )
{
    DBG_ASSERT(tty!=NULL);
    Result_t result = RESULT_OK;

    switch (tty->state) 
    {
        case TS_LOGIN:      result = tty_RunLogin   (tty); break;
        case TS_USER:       result = tty_RunUser    (tty); break;
        case TS_PASSWORD:   result = tty_RunPassword(tty); break;
        case TS_COMMAND:    result = tty_RunCommand (tty); break;
        case TS_REPEAT:     result = tty_RunRepeat  (tty); break;
        case TS_LOCKED:     result = tty_RunLocked  (tty); break;
        default:            DBG_ASSERT(false);
    }
    return result;
}

/*** tty_EndSession() ~ free session context, return to free memory
*/
Result_t tty_EndSession ( TtySession_t *tty )
{
    DBG_ASSERT(tty!=NULL);
    osal_Free(tty);
    return RESULT_OK;
}

/*** tty_RunLogin() ~ prompt for username
*/
static Result_t RunLogin    (TtySession_t *tty);
{
    DBG_ASSERT(TS_LOGIN == tty->state);
    return ERR_NOT_IMPLEMENTED;
}

/*** tty_RunUser() ~ read username input, then prompt for password
*/
static Result_t RunUser     (TtySession_t *tty);
{
    DBG_ASSERT(TS_USER == tty->state);
    return ERR_NOT_IMPLEMENTED;
}

/*** tty_RunPassword() ~ read password input, process user/pwd input
*/
static Result_t RunPassword (TtySession_t *tty);
{
    DBG_ASSERT(TS_PASSWORD == tty->state);
    return ERR_NOT_IMPLEMENTED;
}

/*** tty_RunCommand() ~ read text input stream, process commands
*/
static Result_t RunCommand  (TtySession_t *tty);
{
    DBG_ASSERT(TS_COMMAND == tty->state);
    Result_t result = RESULT_OK;
    switch ( tty->cmd )
    {
        case (CS_PROMPT):   result = cmd_RunPrompt(tty);  break;
        case (CS_INPUT):    result = cmd_RunInput(tty);   break;
        case (CS_EXECUTE):  result = cmd_RunExecute(tty); break;
        case (CS_REPEAT):   result = cmd_RunRepeat(tty);  break;

        default:            result = ERR_NOT_IMPLEMENTED;
                            DBG_ASSERT(false); 
                            break;
    }
    return result;
}

/*** tty_RunLocked() ~ delay login after failed login attempts
*/
static Result_t RunLocked   (TtySession_t *tty);
{
    DBG_ASSERT(TS_LOCKED == tty->state);
    if ( sal_ElapsedMsec(tty->login.time) > tty->login.lock_msec )
        tty->state = TS_
    return ERR_NOT_IMPLEMENTED;
}


/* EOF */