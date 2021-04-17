/* tty_session.h
 *
 * provides context for a given text based terminal session (tty)
 */
#ifndef __TTY_SESSION__
#define __TTY_SESSION__

#include "common.h"
#include "tty_config.h"
#include "tty_command.h"

#define TTY_BUF_CHUNK_SIZE  (128)

#define TTY_PROMPT_STR  "tty-000> "

/*** terminal command/response buffer
*/
typedef struct _TtyBuffer_s
{
    char   *prompt_str;

    struct _TtyBuffer_s *prev_p;    
    struct _TtyBuffer_s *next_p;

    int     idx;    /* cursor location */
    int     len;    /* length of input in this buffer */
    int     size;   /* size of this input buffer */
    bool    insert; /* true=insert chars, false=overwrite */
    Byte_t *buf;

}   TtyBuffer_t;

/*** terminal session state 
*/
typedef enum _TtyState_e
{
    TS_LOGIN=0,     /* begin login sequence */
    TS_USER,        /* read username, prompt password */
    TS_PASSWORD,    /* read password, check credentials */
    TS_COMMAND,     /* process command input state machine */
    TS_LOCKED       /* sign-in locked out, too many attempts */

}   TtyState_t

/*** terminal session context
*/
typedef struct _TtySession_s
{
    TtyConfig_t  cfg;   /* session configuration data */
    TtyBuffer_t  inp;   /* input character buffer */
    TtyBuffer_t  out;   /* output character buffer */
    TtyState_t   state; /* terminal session state */
    CmdState_t   cmd;   /* command state information */

    uint32_t     

} TtySession_t;

/*** terminal session API
*/
Result_t tty_NewSession ( TtySession **tty, TtyConfig_t *cfg );
Result_t tty_RunSession ( TtySession_t *tty );
Result_t tty_EndSession ( TtySession_t *tty );

#endif /* __TTY_SESSION__ */
