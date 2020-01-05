/** @file CircularBuffer.h
 * 
 * @brief 
 * Circular buffer library for embedded systems. Uses class template to support
 * various data types. 
 */
#incl
#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

template <class T>
class circular_buffer
{
    public:
        size_t capacity();
        circular_buffer(size_t s);
        ~circular_buffer();
        bool full();
        bool empty();
        void put(T data);
        T get();
        void reset();
        size_t size();

    // Reads from the circular buffer happen at the index kept in "head" of the buffer.
    // Writes happen at the tail of the buffer.
    //
    private:
        void advance_tail();
        void advance_head();
        T max_size;
        T * p_buffer;
        bool b_is_buffer_full;
        int head;
        int tail;
};

//templates must have their declaration and implementation in one header file
//however, if you want to seperate the declaration from the implementation
//you can do so by renaming the .cpp -> .ipp and including the .ipp file
//at the end of the header file
#include "CircularBuffer.ipp"

#endif /* _CIRCULAR_BUFFER_H_ */

/*** end of file ***/
