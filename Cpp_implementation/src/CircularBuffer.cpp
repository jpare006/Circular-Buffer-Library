#include "CircularBuffer.h"

circular_buffer::circular_buffer(size_t s)
{
	max_size = s;
	buffer = new uint8_t[s];
}

circular_buffer::~circular_buffer()
{
	delete[] buffer;
}

uint8_t circular_buffer::size()
{
	return max_size;
}
