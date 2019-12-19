#include "CppUTest/TestHarness.h"
#include "CircularBuffer.h"
#include <cstdint>

static const size_t size = 5;

TEST_GROUP(CircularBuffer)
{
};

TEST(CircularBuffer, InitiCbufClassWithBufferAndSize)
{
	circular_buffer test_cbuf(size);

	CHECK_EQUAL(size, test_cbuf.size());
}