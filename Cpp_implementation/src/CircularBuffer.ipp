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
	if (empty())
	{
		return T();
	}
	T read_data = buffer_[head_];
	advance_head();

	return read_data;
}

template <class T>
void circular_buffer<T>::reset()
{
	head_ = 0;
	tail_ = 0;
	full_ = false;
}

template <class T>
size_t circular_buffer<T>::size()
{
	if (full_)
	{
		return max_size_;
	}
	else if(tail_ > head_)
	{
		return tail_ - head_;
	}
	else if (tail_ < head_)
	{
		return (max_size_ - head_) + tail_;
	}
	else 
	{
		return 0;
	}
}

//********* end public methods *********//



//********* private methods *********//
template <class T>
void circular_buffer<T>::advance_tail()
{
	if(full_)
	{
		head_ = (head_ + 1) % max_size_;
	}
	tail_ = (tail_ + 1) % max_size_;
	full_ = (head_ == tail_);
}

template <class T>
void circular_buffer<T>::advance_head()
{
	head_ = (head_ + 1) % max_size_;
	full_ = false;
}
//********* end private methods *********//