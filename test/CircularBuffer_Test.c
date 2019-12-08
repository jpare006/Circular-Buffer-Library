#include "unity_fixture.h"
#include "CircularBuffer.h"

TEST_GROUP(CircularBuffer);

static size_t size;
static uint8_t * buffer;
cbuf_handle_t test_cbuf;

TEST_SETUP(CircularBuffer)
{
    size = 10;
	buffer = malloc(sizeof(uint8_t) * size);
}

TEST_TEAR_DOWN(CircularBuffer)
{
	free(buffer);
}



TEST(CircularBuffer, InitCbuf)
{	
	test_cbuf = CircularBuffer_Init(buffer, size);

	TEST_ASSERT_NOT_NULL(test_cbuf);
}

TEST(CircularBuffer, CircularBufferEmptyOnInit)
{
	test_cbuf = CircularBuffer_Init(buffer, size);

	TEST_ASSERT_TRUE(CircularBuffer_Empty(test_cbuf));
	TEST_ASSERT_FALSE(CircularBuffer_Full(test_cbuf));
}