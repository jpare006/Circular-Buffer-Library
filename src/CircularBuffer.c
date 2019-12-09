#include "CircularBuffer.h"

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
static void advance_pointer(cbuf_handle_t cbuf)
{
	cbuf->head += 1;
}
/** end **/

cbuf_handle_t circular_buf_init(uint8_t * buffer, size_t size)
{
	cbuf_handle_t cbuf = malloc(sizeof(circular_buf_t));
	cbuf->buffer = buffer;
	cbuf->max = size;
	cbuf->head = 0;
	cbuf->tail = 0;
	cbuf->full = FALSE;

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
	cbuf->buffer[cbuf->head] = data;

	if (cbuf->head + 1 == cbuf->max)
	{
		cbuf->full = TRUE;
	}
	advance_pointer(cbuf);
}

size_t circular_buf_capacity(cbuf_handle_t cbuf)
{
	return cbuf->max;
}