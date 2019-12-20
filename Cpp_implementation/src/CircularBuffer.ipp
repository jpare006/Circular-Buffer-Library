#include "CircularBuffer.h"

//********* public methods *********//
template <class T>
circular_buffer<T>::circular_buffer(size_t s)
{
	max_size_ = s;
	buffer_ = new T[s];
	full_ = false;
	head_ = 0;
	tail_ = 0;
}

template <class T>
circular_buffer<T>::~circular_buffer()
{
	delete[] buffer_;
}

template <class T>
size_t circular_buffer<T>::capacity()
{
	return max_size_;
}

template <class T>
bool circular_buffer<T>::full()
{
	return full_;
}

template <class T>
bool circular_buffer<T>::empty()
{
	if((head_ == tail_) && !full_)
	{
		return true;
	}
	return false;
}

template <class T>
void circular_buffer<T>::put(T data)
{
	buffer_[tail_] = data;

	advance_tail();
}

template <class T>
T circular_buffer<T>::get()
{
	T read_data;

	read_data = buffer_[head_];
	advance_head();

	return read_data;
}

//********* end public methods *********//



//********* private methods *********//
template <class T>
void circular_buffer<T>::advance_tail()
{
	if((tail_+ 1) == max_size_)
	{
		full_ = true;
	}
	tail_ += 1;
}

template <class T>
void circular_buffer<T>::advance_head()
{
	head_ += 1;
}
//********* end private methods *********//