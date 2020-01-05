/** @file CircularBuffer.ipp
 * 
 * @brief 
 * Circular buffer library for embedded systems. Uses class template to support
 * various data types. 
 */
#include "CircularBuffer.h"

/*!
 * @brief Circular buffer constructor
 * @param[in] s Size with which to initialize buffer
 */
template <class T>
circular_buffer<T>::circular_buffer (size_t s)
{
    max_size = s;
    p_buffer = new T[s];
    b_is_buffer_full = false;
    head = 0;
    tail = 0;
}

/*!
 * @brief Circular buffer destructor
 */
template <class T>
circular_buffer<T>::~circular_buffer ()
{
    delete[] p_buffer;
}

/*!
 * @brief Find the maximum number of elements the circular buffer can store.
 * @return Maximum size of the circular buffer.
 */
template <class T>
size_t circular_buffer<T>::capacity ()
{
    return max_size;
}

/*!
 * @brief Check if the circular buffer is full or not.
 * @return Boolean value answering if circular buffer is full or not.
 */
template <class T>
bool circular_buffer<T>::full ()
{
    return b_is_buffer_full;
}

/*!
 * @breif Check if circular buffer is empty or not.
 * @return Boolean value answering if circular buffer is empty or not.
 */
template <class T>
bool circular_buffer<T>::empty ()
{
    if ((head == tail) && !b_is_buffer_full)
    {
        return true;
    }

    return false;
}

/*!
 * @brief Place a single data element into the underlying buffer.
 * @param[in] data Data element to be stored in circular buffer.
 */
template <class T>
void circular_buffer<T>::put (T data)
{
    p_buffer[tail] = data;

    advance_tail();
}

/*!
 * @brief Read the next value in the circular buffer.
 * @return Value read from buffer.
 */
template <class T>
T circular_buffer<T>::get ()
{
    if (empty())
    {
        return T();
    }

    T value = p_buffer[head];
    advance_head();

    return value;
}

/*!
 * @brief Reset the circular buffer to its initial state.
 */
template <class T>
void circular_buffer<T>::reset ()
{
    head = 0;
    tail = 0;
    b_is_buffer_full = false;
}

/*!
 * @brief Calculate the current number of elements in the circular buffer.
 * @return Number of elements currently in circular buffer.
 */
template <class T>
size_t circular_buffer<T>::size ()
{
    size_t value = -1;

    if (b_is_buffer_full)
    {
        value = max_size;
    }
    else if (tail > head)
    {
        value = tail - head;
    }
    else if (tail < head)
    {
        //Use buffer max value to calculate amount of elements
        value = (max_size - head) + tail;
    }
    else 
    {
        //At this point, the only option left is: (tail == head  == 0) && !full
        value = 0;
    }

    return value;
}

/*!
 * @brief Advance the circular buffer tail index.
 *
 * @par 
 * This function is always called when a write to the circular buffer has been
 * made and the value has already been written to the underlying buffer.
 */
template <class T>
void circular_buffer<T>::advance_tail ()
{
    if (b_is_buffer_full)
    {
        head = (head + 1) % max_size;
    }

    tail = (tail + 1) % max_size;
    b_is_buffer_full = (head == tail);
}

/*!
 * @brief Advance the circular buffer head index.
 *
 * @par 
 * This function is always called when a circular buffer read is made. It is
 * called after the data has already been read.
 */
template <class T>
void circular_buffer<T>::advance_head ()
{
    head = (head + 1) % max_size;
    b_is_buffer_full = false;
}

/*** end of file ***/
