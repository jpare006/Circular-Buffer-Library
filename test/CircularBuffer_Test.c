#include "unity_fixture.h"
#include "CircularBuffer.h"

TEST_GROUP(CircularBuffer);

TEST_SETUP(CircularBuffer)
{
}

TEST_TEAR_DOWN(CircularBuffer)
{
}

TEST(CircularBuffer, CreateCbufHandle)
{	
	cbuf_handle_t test_cbuf;
	test_cbuf = CircularBuffer_Init();

	TEST_ASSERT_NOT_NULL(test_cbuf);
}