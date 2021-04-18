/* tty_session.h
 *
 * provides context for a given text based terminal session (tty)
 */
#ifndef __TTY_SESSION__
#define __TTY_SESSION__

#include "common.h"
#include "buffer.h"
#include "tty_command.h"

#define TTY_PROMPT_STR  "tty-000> "

#define PROMPT_STR_SIZE  (64)


/*** input buffer, with edit cursor information
*/
typedef struct _TtyInput_s
{

    Buffer_t *buf;
    int     cursor;         /* cursor location */
    bool    insert;         /* true=insert chars, false=overwrite */

}   TtyInput_t;

/*** output buffer cannot be modified, only written to
*/
typedef struct _TtyOutput_s
{

    Buffer_t *buf;

}   TtyOutput_t;

/*** terminal session state 
*/
typedef enum _TtyState_e
{
    TS_LOGIN=0,             /* begin login sequence */
    TS_USER,                /* read username, prompt password */
    TS_PASSWORD,            /* read password, check credentials */
    TS_COMMAND,             /* process command input state machine */
    TS_LOCKED               /* sign-in locked out, too many attempts */

}   TtyState_t

/*** application supplied ASCII i/o API
 * 
 * input arg: ch = ptr to input buffer where character is stored
 * return:  0 = char recieved 
 *         -1 = no char available
 *         else, serial interface specific error
 */
typedef int (GetChar_FP)(uint8_t *ch);
typedef int (PutChar_FP)(uint8_t  ch);

/*** terminal session options
*/
typedef struct _TtyOptions_s
{
    bool password;      /* challenge start of session with password check */
    bool echo;          /* echo input character stream to output stream */
    bool edit;          /* allow line editing (left and right arrows) */
    bool history;       /* allow line history (up and down arrows) */
    int  delay_ms;      /* auto-repeat delay */
    uint64_t timestamp; /* 64-bit timestamp field */

}   TtyOptions_t;

#define TTY_OPTIONS_INIT {      \
        .password = false,      \
        .echo = true,           \
        .edit = false,          \
        .history = false,       \
        .delay_ms = MSEC(333)   }

/*** session login information
*/
typedef struct _TtyLogin_s
{
    char username[TTY_USERNAME_SIZE];
    char password[TTY_PASSWORD_SIZE];

    bool     locked;   /* true when max # attempts exceeded */
    uint64_t time;    /* last login attempt, ctr=0 after a period */
    uint32_t ctr;     /* bumped on every login attempt */
    uint32_t id;      /* unique login ID */

}   TtyLogin_t;

#define TTY_LOGIN_INIT {   \
        .username = "",    \
        .password = ""     \
        .locked = false    }

/*** terminal session configuration
*/
typedef struct _TtyConfig_s
{
    GetChar_FP     *GetChar;
    PutChar_FP     *PutChar;
    TtyOptions_t    opt;
    TtyLogin_t      login;

}   TtyConfig_t;

#define TTY_CONFIG_INIT {   \
        .GetChar=NULL,      \
        .PutChar=NULL,      \
        .opt = TTY_OPTIONS_INIT, \
        .login = TTY_LOGIN_INIT }

/*** terminal session context
*/
typedef struct _TtySession_s
{
    char prompt_str[PROMPT_STR_SIZE];

    TtyConfig_t  cfg;       /* session configuration data */
    TtyInput_t   inp;       /* intput character buffer */
    TtyOutput_t  out;       /* output character buffer */
    TtyState_t   state;     /* terminal session state */
    CmdState_t   cmd;       /* command state information */

} TtySession_t;

/*** terminal session API
*/
Result_t tty_NewSession ( TtySession **tty, TtyConfig_t *cfg );
Result_t tty_RunSession ( TtySession_t *tty );
Result_t tty_EndSession ( TtySession_t *tty );

#endif /* __TTY_SESSION__ */
