# TTY
A text based terminal interface framework. Command definitions provide the application specific syntax and back-end functionality.  Bash style command syntax is used (non-POSIX) e.g., cmd -abc -f100 -g"any string"

## Source Files
* common.h - included first in every source file by convention
* main.c - TTY test program
* my_assert.[c,h] - debug assert definitions
* result.h - function return codes
* sal.[c,h] - system abstraction layer
* tty_alloc.[c,h] - text buffer allocation mgmt
* tty_command.[c,h] - command processing state machine
* tty_config.h - configuration definition
* tty_session.[c,h] - terminal session API and definitions