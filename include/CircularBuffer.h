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


cbuf_handle_t CircularBuffer_Init(void);


#endif /*_CIRUCULAR_BUFFER_H_*/