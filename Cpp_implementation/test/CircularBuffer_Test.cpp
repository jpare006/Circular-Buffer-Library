#include "CppUTest/TestHarness.h"
#include "CircularBuffer.h"
#include <cstdint>

static const size_t size = 5;
static uint8_t data[] = {1,2,3,4,5};
static uint8_t read_data;

TEST_GROUP(CircularBuffer)
{
};


//************* begin tests *************//
TEST(CircularBuffer, InitiCbufClassWithBufferAndSize)
{
	circular_buffer<uint8_t> test_cbuf(size);

	CHECK_EQUAL(size, test_cbuf.size());
}

TEST(CircularBuffer, CbufStateAfterInitIsEmpty)
{
	circular_buffer<uint8_t> test_cbuf(size);

	CHECK_FALSE(test_cbuf.full());
	CHECK(test_cbuf.empty());
}

TEST(CircularBuffer, AddFirstDataElementToCbufAndReadIt)
{
	circular_buffer<uint8_t> test_cbuf(size);

	test_cbuf.put(data[0]);
	read_data = test_cbuf.get();

	LONGS_EQUAL(data[0], read_data);

}

//************* end tests *************//