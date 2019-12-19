#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

class circular_buffer
{
public:
	uint8_t size();
	circular_buffer(size_t s);
	~circular_buffer();
private:
	uint8_t max_size;
	uint8_t * buffer;
};


#endif /* _CIRCULAR_BUFFER_H_ */