#ifndef _CIRUCULAR_BUFFER_H_
#define _CIRUCULAR_BUFFER_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef int BOOL;

//Opaque circular buffer structure, forward declaration
typedef struct circular_buf_t circular_buf_t;

//Handle type, the way users interact with the API
typedef circular_buf_t* cbuf_handle_t;


cbuf_handle_t CircularBuffer_Init(uint8_t * buffer, size_t size);
BOOL CircularBuffer_Empty(cbuf_handle_t cbuf);
BOOL CircularBuffer_Full(cbuf_handle_t cbuf);
void CircularBuffer_Put(cbuf_handle_t cbuf, uint8_t data);
size_t CircularBuffer_Capacity(cbuf_handle_t cbuf);

#endif /*_CIRUCULAR_BUFFER_H_*/