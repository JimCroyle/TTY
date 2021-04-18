/* buffer.h
 *
 * dynamically sized buffer API 
 */
#ifndef __BUFFER__
#define __BUFFER__

#include "common.h"

#define NUM_BLOCKS  (100)
#define BLOCK_SIZE  (128)

typedef struct _Buffer_s
{
    struct _Buffer_s *next;
    struct _Buffer_s *prev;

    char data[BLOCK_SIZE];
    
}   Buffer_t;

#endif /* __BUFFER__ */
