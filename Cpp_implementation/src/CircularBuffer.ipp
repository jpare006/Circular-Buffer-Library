#include "CircularBuffer.h"

template <class T>
circular_buffer<T>::circular_buffer(size_t s)
{
	max_size = s;
	buffer = new T[s];
}

template <class T>
circular_buffer<T>::~circular_buffer()
{
	delete[] buffer;
}

template <class T>
size_t circular_buffer<T>::size()
{
	return max_size;
}
