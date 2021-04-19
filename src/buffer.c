/* buffer.c
 *
 * memory allocation API for dynamically sized text buffers
 * input and output buffers are dynamically allocated
 * in small blocks as needed.
 */
#include "common.h"
#include "buffer.h"

/* list of available buffers to allocate
 * full list of all buffers
 */
static Buffer_t *free_list=NULL;
static Buffer_t *buf_heap=NULL;

Buffer_t *buf_GetHeap(void);
Buffer_t *buf_GetFree(void);

#define BUFFER_HEAP_SIZE  (NUM_BLOCKS * sizeof(Buffer_t))

/*** buf_Init() ~ initialize block allocation 
*/
Result_t buf_Init ( void )
{
    Result_t result = SUCCESS;
    Byte_t *buf = sal_Malloc(BUFFER_HEAP_SIZE);
    if ( NULL == buf )
    {
        result = ERR_ALLOC_FAIL;
    }
    else
    {
        buf_heap = buf;

        /* initialize buffer structure, link buffers
        */
        memset(buf, 0, BUFFER_HEAP_SIZE);
        for (int i=0; i < NUM_BLOCKS; i++)
        {

            buf[i].prev = i ? &buf[i-1] : NULL;
            buf[i].next = &buf[i+1];
            buf[i].sentinel = BUFFER_SENTINEL;
        }
        buf[NUM_BLOCKS-1].next = NULL;
        free_list = buf;
    }
    return result;
}

/*** buf_Alloc() ~ allocate a new block and link it as next
*
* returns NULL if no blocks available, otherwise ptr to 
* allocated block is returned (buf->next)
*/
Buffer_t *buf_Alloc ( Buffer_t *buf )
{
    DBG_ASSERT(buf!=NULL);
    Buffer_t *newbuf = free_list;
    if ( newbuf )
    {
        /* insert block 
        */
        newbuf->prev = buf;
        newbuf->next = buf->next;
        buf->next = newbuf;
        free_list = free_list->next;
    }
    return newbuf;
}

/*** buf_Free() ~ de-allocate a block, move it to free list 
*
* returns ptr to next block linked to buffer being freed
*/
Buffer_t * buf_Free ( Buffer_t *buf )
{
    DBG_ASSERT(buf!=NULL);
    DBG_ASSERT(BUFFER_SENTINEL, buf->sentinel);
    Buffer_t *prev = buf->prev;
    Buffer_t *next = buf->next;
    if ( prev )
    {
        prev->next = next;
    }
    if ( buf->next )
    {
        buf->next->prev = prev;
    }
    buf->prev = NULL;
    buf->next = free_list;
    free_list->prev = buf;
    free_list = buf;
    return next;
}

/*** buf_Nuke() ~ de-allocate the entire chain of blocks
* 
* note: does not free up blocks previous to buffer passed in.
* returns previous block buffer ptr
*/
Buffer_t * buf_Nuke ( Buffer_t *buf )
{
    BUffer_t *prev = buf->prev;
    DBG_ASSERT(buf!=NULL);
    if (prev)
        prev->next = NULL;

    while ( buf = buf_Free(buf); )

    return prev;
}

/* EOF */