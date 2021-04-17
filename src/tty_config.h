/* tty_config.h
 *
 * provides configuration and options data structure for MyTty session
 */
#ifndef __TTY_CONFIG__
#define __TTY_CONFIG__

#include "common.h"

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

#endif /* __TTY_CONFIG__ */
