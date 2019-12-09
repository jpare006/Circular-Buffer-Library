#include "unity_fixture.h"
#include "CircularBuffer.h"

TEST_GROUP(CircularBuffer);

static size_t size = 5;
static uint8_t * buffer;
cbuf_handle_t test_cbuf;
static uint8_t data[] = {1, 2, 3, 4, 5};

TEST_SETUP(CircularBuffer)
{
	buffer = malloc(sizeof(uint8_t) * size);
	test_cbuf = CircularBuffer_Init(buffer, size);

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

IGNORE_TEST(CircularBuffer, UserBufferSizeLessThanOneProducesError)
{
	//TODO: write code to produce error on size that is too small
}

TEST(CircularBuffer, AddFirstDataElementToCircularBuffer)
{
	CircularBuffer_Put(test_cbuf, data[0]);

	TEST_ASSERT_EQUAL_UINT8(data[0], buffer[0]);
}

TEST(CircularBuffer, CapacityMethodReturnsCorrectValue)
{
	TEST_ASSERT_EQUAL_size_t(size, CircularBuffer_Capacity(test_cbuf));
}

TEST(CircularBuffer, AddMultipleDataElementsToCircularBuffer)
{
	CircularBuffer_Put(test_cbuf, data[0]);
	CircularBuffer_Put(test_cbuf, data[1]);
	CircularBuffer_Put(test_cbuf, data[2]);

	TEST_ASSERT_EQUAL_UINT8(data[0], buffer[0]);
	TEST_ASSERT_EQUAL_UINT8(data[1], buffer[1]);
	TEST_ASSERT_EQUAL_UINT8(data[2], buffer[2]);

}