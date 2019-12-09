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


cbuf_handle_t circular_buf_init(uint8_t * buffer, size_t size);
BOOL circular_buf_empty(cbuf_handle_t cbuf);
BOOL circular_buf_full(cbuf_handle_t cbuf);
void circular_buf_put(cbuf_handle_t cbuf, uint8_t data);
size_t circular_buf_capacity(cbuf_handle_t cbuf);
void circular_buf_reset(cbuf_handle_t cbuf);
uint8_t circular_buf_get(cbuf_handle_t cbuf);

#endif /*_CIRUCULAR_BUFFER_H_*/