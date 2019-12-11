#include "CircularBuffer.h"

//reads happen at the head of the buffer
//writes happen at the tail of the buffer

struct circular_buf_t
{
    uint8_t * buffer;
    size_t head;
    size_t tail;
    size_t max; //of the buffer
    BOOL full;
};

enum {TRUE = 1, FALSE = 0};

/** Helper Functions **/
static void advance_write_pointer(cbuf_handle_t cbuf)
{
    if (cbuf->full)
    {
        cbuf->head = (cbuf->head + 1) % cbuf->max;
    }

    cbuf->tail = (cbuf->tail + 1) % cbuf->max;
    cbuf->full = (cbuf->head == cbuf->tail);
}

static void advance_read_pointer(cbuf_handle_t cbuf)
{
    cbuf->head = (cbuf->head + 1) % cbuf->max;
    cbuf->full = (cbuf->head == cbuf->tail);
}
/** end **/

cbuf_handle_t circular_buf_init(uint8_t * buffer, size_t size)
{
    cbuf_handle_t cbuf = malloc(sizeof(circular_buf_t));
    cbuf->buffer = buffer;
    cbuf->max = size;
    circular_buf_reset(cbuf);

    return cbuf;
}

BOOL circular_buf_empty(cbuf_handle_t cbuf)
{
    if(cbuf->head == cbuf->tail && !cbuf->full)
    {
        return TRUE;
    }

    return FALSE;
}

BOOL circular_buf_full(cbuf_handle_t cbuf)
{
    return cbuf->full;
}

void circular_buf_put(cbuf_handle_t cbuf, uint8_t data)
{
    cbuf->buffer[cbuf->tail] = data;

    advance_write_pointer(cbuf);
}

size_t circular_buf_capacity(cbuf_handle_t cbuf)
{
    return cbuf->max;
}

void circular_buf_reset(cbuf_handle_t cbuf)
{
    cbuf->head = 0;
    cbuf->tail = 0;
    cbuf->full = FALSE;
}

int circular_buf_get(cbuf_handle_t cbuf, uint8_t * data_read)
{
    int status = -1;

    if(!circular_buf_empty(cbuf))
    {
        status = 0;

        *data_read = cbuf->buffer[cbuf->head];
        advance_read_pointer(cbuf);

        return status;
    }

    return status;
}

size_t circular_buf_size(cbuf_handle_t cbuf)
{
    if(circular_buf_full(cbuf))
    {
        return cbuf->max;
    }
    else if(cbuf->tail > cbuf->head)
    {
        return cbuf->tail - cbuf->head;
    }
    else if (cbuf->tail < cbuf->head)
    {
        return (cbuf->max - cbuf->head) + cbuf->tail;
    }
    else
    {
        //only option left: tail == head && !full
        return 0;
    }
}