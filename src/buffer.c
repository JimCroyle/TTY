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

static int buf_num_blocks = 0;
static int buf_block_size = 0;
static int buf_heap_size = 0;

/*** buf_GetBlockFree() ~ get # free data in buffer block
*/
int buf_GetBlockAvail (Buffer_t *buf)
{
    buf_Validate(buf);
    return buf_block_size - buf->len;
}

/*** buf_Init() ~ initialize block allocation 
*/
Result_t buf_Init ( int num_blocks, int block_size )
{
    Result_t result = SUCCESS;
    buf_heap_size = num_blocks * block_size;
    Byte_t *buf = sal_Malloc(buf_heap_size);
    if ( NULL == buf )
    {
        result = ERR_ALLOC_FAIL;
        buf_heap_size *= -1;
    }
    else
    {
        buf_num_blocks = num_blocks;
        buf_block_size = block_size;
        buf_heap = buf;

        /* initialize buffer structure, link buffers
        */
        memset(buf, 0, buf_heap_size);
        for (int i=0; i < buf_num_blocks; i++)
        {

            buf[i].prev = i ? &buf[i-1] : NULL;
            buf[i].next = &buf[i+1];
            buf[i].sentinel = BUFFER_SENTINEL;
        }
        buf[buf_num_blocks-1].next = NULL;
        free_list = buf;
    }
    return result;
}

/*** buf_Assert() ~ assert on value integrity during debug
*/
void buf_Assert (Buffer_t *buf)
{
    DBG_ASSERT(buf);
    DBG_ASSERT(buf->len >= 0);
    DBG_ASSERT(buf->len <= BLOCK_SIZE);
    DBG_ASSERT(! buf->next || BLOCK_SIZE == buf->len )
    DBG_ASSERT(BUFFER_SENTINEL == buf->sentinel);
}

/*** buf_Alloc() ~ allocate a new block and link it as next
*
* returns NULL if no blocks available, otherwise ptr to 
* allocated block is returned (buf->next)
*/
Buffer_t *buf_Alloc ( Buffer_t *buf )
{
    if (buf)
        buf_Validate(buf);

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
    buf_Validate(buf);
    Buffer_t *prev = buf->prev;
    Buffer_t *next = buf->next;
    if ( prev )
    {
        prev->next = next;
    }
    if ( next )
    {
        next->prev = prev;
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
    buf_Validate(buf);
    BUffer_t *prev = buf->prev;
    if (prev)
        prev->next = NULL;

    for (int i=0; buf; i++)
    {
        DBG_ASSERT(i < NUM_BLOCKS);
        buf = buf_Free(buf);
    } 

    return prev;
}

/*** buf_CopyFromString() ~ copy string to buffer
*
* note, buffer will be extended as needed
* returns # characters copied to buffer
* returns -1 if copy failed (i.e., no available memory)
*/
int buf_CopyFromString ( Buffer_t *buf, char *str )
{
    DBG_ASSERT(str!=NULL);
    buf_Validate(buf);
    Result_t result = RESULT_OK;
    int num = strlen(str);

    while ( num > 0 )
    {
        /* if no space available in buffer, allocate new one
        */
        int avail = (buf_block_size - buf->len);
        if ( ! avail ) 
        {
            buf = buf_Alloc(buf);
            if ( ! buf ) 
            {
                result = ERR_ALLOC_FAIL;
                break;
            }
            avail = (buf_block_size - buf->len);
        }

        /* clamp strcpy() operation if bigger than buffer
        */
        int cnt = ( num > avail ? avail : num );
        memcpy(buf->data, str, cnt);
        buf->len += cnt;
        num -= cnt;
        str += cnt;
        *str = 0;
    }
    return result;
}

/*** buf_CopyToString() ~ copy from buffer to string
*
* assumes string buffer is big enough to handle all data
* returns number of bytes copied from data buffer
*/
int buf_CopyToString ( Buffer_t *buf, char *str, int max)
{
    DBG_ASSERT(str!=NULL);
    buf_Validate(buf);
    int cnt = 0;

    while ( (cnt < max) && buf && buf->len )
    {
        int num = buf->len;
        if ( cnt + num > max )
        {
            num = max - cnt;
        }
        memcpy(str, buf->data, num);
        cnt += num;
        str += num;
        *str = 0;
        buf = buf->next;
    }
    return cnt;
}

/*** buf_CatFromString() ~ concatenate string to buffer
*
* note, buffer will be extended as needed
* returns # characters copied to buffer
* returns -1 if copy failed (i.e., no available memory)
*/
int buf_CatFromString ( Buffer_t *buf, char *str )
{
    DBG_ASSERT(buf!=NULL);
    DBG_ASSERT(str!=NULL);
    int retval = -1;
    int cnt;

    while ( buf->next )
    {
        DBG_ASSERT(BLOCK_SIZE == buf->len);
        buf = buf->next;
    }
    return buf_CopyFromString(buf,str);
}

/* EOF */