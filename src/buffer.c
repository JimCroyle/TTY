/* buffer.c
 *
 * memory allocation API for terminal text buffers
 * input and output buffers are dynamically allocated
 * in small blocks as needed.
 */
#include "common.h"
#include "buffer.h"

/* list of available buffers to allocate
 * full list of all buffers
 */
static Buffer_t *free_list=NULL;
static Buffer_t *full_list=NULL;

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
        /* initialize buffer structure, link buffers
        */
        memset(buf, 0, BUFFER_HEAP_SIZE);
        for (int i=0; i < NUM_BLOCKS; i++)
        {

            buf[i].prev = i ? &buf[i-1] : NULL;
            buf[i].next = &buf[i+1];
        }
        buf[NUM_BLOCKS-1].next = NULL;
        free_list = buf;
        full_list = buf;
    }
    return result;
}

/*** buf_Allocate, allocate a new block and link to buf
*/
Buffer_t *buf_Allocate ( Buffer_t *buf )
{
    DBG_ASSERT(buf!=NULL);
}

/* EOF */