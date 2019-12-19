#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

template <class T>
class circular_buffer
{
	public:
		size_t size();
		circular_buffer(size_t s);
		~circular_buffer();
	private:
		T max_size;
		T * buffer;
};

#include "CircularBuffer.ipp"

#endif /* _CIRCULAR_BUFFER_H_ */