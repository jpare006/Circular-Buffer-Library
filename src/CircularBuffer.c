#include "CircularBuffer.h"


struct circular_buf_t
{
	uint8_t * buffer;
	size_t head;
	size_t tail;
	size_t max; //of the buffer
	BOOL full;
};

struct circular_buf_t* CircularBuffer_Init(void)
{
	struct circular_buf_t* cbuf = malloc(sizeof(struct circular_buf_t));

	return cbuf;
}