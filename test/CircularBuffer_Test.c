#include "unity_fixture.h"
#include "CircularBuffer.h"
#include <stdio.h>

TEST_GROUP(CircularBuffer);

static size_t size = 5;
static uint8_t * buffer;
cbuf_handle_t test_cbuf;
static uint8_t data[] = {1, 2, 3, 4, 5};

/** Helper functions **/
static void fill_buffer(cbuf_handle_t test_cbuf)
{
    for(size_t i = 0; i < size; i++)
    {
        circular_buf_put(test_cbuf, data[i]);
    }
}

static void fill_buffer_num_elements(cbuf_handle_t test_cbuf, size_t num)
{
    for(uint8_t i = 0; i < num; i++)
    {
        circular_buf_put(test_cbuf, i);
    }
}
/** end helper **/

TEST_SETUP(CircularBuffer)
{
    buffer = malloc(sizeof(uint8_t) * size);
    test_cbuf = circular_buf_init(buffer, size);

}

TEST_TEAR_DOWN(CircularBuffer)
{
    free(buffer);
}



TEST(CircularBuffer, InitCbuf)
{   
    test_cbuf = circular_buf_init(buffer, size);

    TEST_ASSERT_NOT_NULL(test_cbuf);
}

TEST(CircularBuffer, CircularBufferEmptyOnInit)
{
    test_cbuf = circular_buf_init(buffer, size);

    TEST_ASSERT_TRUE(circular_buf_empty(test_cbuf));
    TEST_ASSERT_FALSE(circular_buf_full(test_cbuf));
}

IGNORE_TEST(CircularBuffer, UserBufferSizeLessThanOneProducesError)
{
    //TODO: write code to produce error on size that is too small
}

TEST(CircularBuffer, AddFirstDataElementToCircularBuffer)
{
    circular_buf_put(test_cbuf, data[0]);

    TEST_ASSERT_EQUAL_UINT8(data[0], buffer[0]);
}

TEST(CircularBuffer, CapacityMethodReturnsCorrectValue)
{
    TEST_ASSERT_EQUAL_size_t(size, circular_buf_capacity(test_cbuf));
}

TEST(CircularBuffer, AddMultipleDataElementsToCircularBuffer)
{
    circular_buf_put(test_cbuf, data[0]);
    circular_buf_put(test_cbuf, data[1]);
    circular_buf_put(test_cbuf, data[2]);

    TEST_ASSERT_EQUAL_UINT8(data[0], buffer[0]);
    TEST_ASSERT_EQUAL_UINT8(data[1], buffer[1]);
    TEST_ASSERT_EQUAL_UINT8(data[2], buffer[2]);
}

TEST(CircularBuffer, CbufFullFunctionReturnsTrueWhenFull)
{
    fill_buffer(test_cbuf);

    TEST_ASSERT_TRUE(circular_buf_full(test_cbuf));
}

TEST(CircularBuffer, AddingTwoMoreElementsAfterFullOverwritesOldestElements)
{
    fill_buffer(test_cbuf);

    circular_buf_put(test_cbuf, 6);
    circular_buf_put(test_cbuf, 7);

    TEST_ASSERT_EQUAL_UINT8(6, buffer[0]);
    TEST_ASSERT_EQUAL_UINT8(7, buffer[1]);
    //rest of buffer should not be overwritten yet
    TEST_ASSERT_EQUAL_UINT8(3, buffer[2]);
}

TEST(CircularBuffer, AddingMultipleElementsAfterFullContinuesToOverwriteOldestElements)
{
    //2 rounds around the buffer
    fill_buffer_num_elements(test_cbuf, size * 2);

    //plus an extra overwrite
    circular_buf_put(test_cbuf, size * 2);

    TEST_ASSERT_EQUAL_UINT8(8, buffer[3]);
    TEST_ASSERT_EQUAL_UINT8(9, buffer[4]);
    TEST_ASSERT_EQUAL_UINT8(10, buffer[0]);

}

TEST(CircularBuffer, ResetFuncSetsCbufHeadAndTailBackToZeroAndFullToFalse)
{
    fill_buffer(test_cbuf);

    circular_buf_reset(test_cbuf);

    //call empty to check if reset worked
    TEST_ASSERT_TRUE(circular_buf_empty(test_cbuf));
    TEST_ASSERT_FALSE(circular_buf_full(test_cbuf));
}

TEST(CircularBuffer, GetElementFromCircularBuffer)
{
    uint8_t data_read;

    circular_buf_put(test_cbuf, data[0]);
    data_read = circular_buf_get(test_cbuf);

    TEST_ASSERT_EQUAL_UINT8(data[0], data_read);
}

TEST(CircularBuffer, GetTwoElementsFromCircularBuffer)
{
    uint8_t data_read[] = {0, 0};

    circular_buf_put(test_cbuf, data[0]);
    circular_buf_put(test_cbuf, data[1]);
    data_read[0] = circular_buf_get(test_cbuf);
    data_read[1] = circular_buf_get(test_cbuf);

    TEST_ASSERT_EQUAL_UINT8(data[0], data_read[0]);
    TEST_ASSERT_EQUAL_UINT8(data[1], data_read[1]);
}

//TODO: issue with incrementing pointers when buffer is full
TEST(CircularBuffer, HeadPointerIsUpdatedAfterSingleOverwriteOccurs)
{
    uint8_t data_read;

    fill_buffer(test_cbuf);
    //overwrite oldest data element
    circular_buf_put(test_cbuf, 150);

    //read data from heads new location
    data_read = circular_buf_get(test_cbuf);

    //data at heads original loc. is overwritten by 150
    //head must advanced to maintain FIFO functionality
    TEST_ASSERT_EQUAL_UINT8(data[1], data_read);
}

TEST(CircularBuffer, ReadMaxSizeElementsAfterOverwrite)
{
    uint8_t expected_read[] = {2, 3, 4, 5, 6};
    uint8_t actual_read[5] = {0};
    
    fill_buffer(test_cbuf);
    //overwrite oldest element (data overwritten = 1)
    circular_buf_put(test_cbuf, 6);

    //read max size elements after overwrite
    for(size_t i = 0; i < size; i++)
    {
        actual_read[i] = circular_buf_get(test_cbuf);
    }

    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_read, actual_read, size);
}

TEST(CircularBuffer, FullFlagSetToZeroAfterReadOcurs)
{
    fill_buffer(test_cbuf);
    TEST_ASSERT_TRUE(circular_buf_full(test_cbuf));

    circular_buf_get(test_cbuf);
    TEST_ASSERT_FALSE(circular_buf_full(test_cbuf));

}

IGNORE_TEST(CircularBuffer, ReadMaxSizeElementsAfterMultipleOverwrite)
{

}

