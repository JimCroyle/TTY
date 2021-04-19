/* buffer.h
 *
 * dynamically sized buffer API 
 */
#ifndef __BUFFER__
#define __BUFFER__

#include "common.h"

#define NUM_BLOCKS  (108)
#define BLOCK_SIZE  (128)

/* lead+trail zero in sentinel value for passive null term 
 * for data[] in case runaway string (both endianities)
 */
#define BUFFER_SENTINEL (0x00BEEF00)

typedef struct _Buffer_s
{
    uint32_t id;  /* useable by caller/application */

    struct _Buffer_s *next;
    struct _Buffer_s *prev;

    int  len;
    char data[BLOCK_SIZE];
    const uint32_t sentinel;
    
}   Buffer_t;


/*** functional prototypes
*/
extern Result_t  buf_Init  (int num_blocks, int block_size);
extern void      buf_Assert(Buffer_t *buf);
extern Buffer_t *buf_Alloc (Buffer_t *buf);
extern Buffer_t *buf_Free  (Buffer_t *buf);
extern Buffer_t *buf_Nuke  (Buffer_t *buf);

/*** buffer copy routines (CopyTo, copies to buffer)
*/
extern int  buf_CopyFromString (Buffer_t *buf, char *str);
extern int  buf_CopyToString   (Buffer_t *buf, char *str, int max);
extern int  buf_CatFromString  (Buffer_t *buf, char *str);

#endif /* __BUFFER__ */
