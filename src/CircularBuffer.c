#include "CircularBuffer.h"


struct circular_buf_t
{
	uint8_t * buffer;
	size_t head;
	size_t tail;
	size_t max; //of the buffer
	BOOL full;
};

cbuf_handle_t CircularBuffer_Init(void)
{
	cbuf_handle_t cbuf = malloc(sizeof(circular_buf_t));

	return cbuf;
}