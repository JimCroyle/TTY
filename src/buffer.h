/* buffer.h
 *
 * dynamically sized buffer API 
 */
#ifndef __BUFFER__
#define __BUFFER__

#include "common.h"

#define NUM_BLOCKS  (1008)
#define BLOCK_SIZE  (128)

#define BUFFER_SENTINEL (0xBABEFACE)

typedef struct _Buffer_s
{
    uint32_t id;

    struct _Buffer_s *next;
    struct _Buffer_s *prev;

    char data[BLOCK_SIZE];
    const uint32_t null_term; /* 0 */
    uint32_t sentinel;
    
}   Buffer_t;

/*** functional prototypes
*/
void      buf_Init  (void);
Buffer_t *buf_Alloc (Buffer_t *buf);
Buffer_t *buf_Free  (Buffer_t *buf);
Buffer_t *buf_Nuke  (Buffer_t *buf);

Buffer_t *buf_GetHeap (void);
Buffer_t *buf_GetFree (void);

#endif /* __BUFFER__ */
