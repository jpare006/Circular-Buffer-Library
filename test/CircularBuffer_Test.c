#include "unity_fixture.h"
#include "CircularBuffer.h"
#include <stdio.h>

TEST_GROUP(CircularBuffer);

static size_t size = 5;
static uint8_t * buffer;
cbuf_handle_t test_cbuf;
static uint8_t data[] = {1, 2, 3, 4, 5};
static size_t elements_in_cbuf;

//************* Helper functions *************//
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
//************* end helper *************//

TEST_SETUP(CircularBuffer)
{
    elements_in_cbuf = size + 1;
    buffer = malloc(sizeof(uint8_t) * size);
    test_cbuf = circular_buf_init(buffer, size);

}

TEST_TEAR_DOWN(CircularBuffer)
{
    free(buffer);
}

//************* begin tests *************//

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
    circular_buf_get(test_cbuf, &data_read);

    TEST_ASSERT_EQUAL_UINT8(data[0], data_read);
}

TEST(CircularBuffer, GetTwoElementsFromCircularBuffer)
{
    uint8_t data_read[] = {0, 0};

    circular_buf_put(test_cbuf, data[0]);
    circular_buf_put(test_cbuf, data[1]);

    circular_buf_get(test_cbuf, &data_read[0]);
    circular_buf_get(test_cbuf, &data_read[1]);

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
    circular_buf_get(test_cbuf, &data_read);

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
        circular_buf_get(test_cbuf, &actual_read[i]);
    }

    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_read, actual_read, size);
}

TEST(CircularBuffer, FullFlagSetToZeroAfterReadOcurs)
{
    uint8_t temp;

    fill_buffer(test_cbuf);
    TEST_ASSERT_TRUE(circular_buf_full(test_cbuf));

    circular_buf_get(test_cbuf, &temp);
    TEST_ASSERT_FALSE(circular_buf_full(test_cbuf));

}

TEST(CircularBuffer, ReadMaxSizeElementsAfterMultipleOverwrites)
{
    uint8_t expected_read[] = {5, 6, 7, 8, 9};
    uint8_t actual_read[5] = {0};
    
    fill_buffer_num_elements(test_cbuf, size * 2);

    //read max size elements after overwrites
    for(size_t i = 0; i < size; i++)
    {
        circular_buf_get(test_cbuf, &actual_read[i]);
    }

    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected_read, actual_read, size);
}

TEST(CircularBuffer, ReadWhenBufferEmptyReturnsErrorToUser)
{
    uint8_t temp;

    int status;
    circular_buf_reset(test_cbuf);
    status = circular_buf_get(test_cbuf, &temp);

    TEST_ASSERT_EQUAL_INT(-1, status);
}

TEST(CircularBuffer, SizeFuncReturnsZeroWhenCbufEmpty)
{
    elements_in_cbuf = circular_buf_size(test_cbuf);

    TEST_ASSERT_EQUAL_size_t(0, elements_in_cbuf);
}

TEST(CircularBuffer, SizeFuncReturnMaxSizeWhenCbufFull)
{
    fill_buffer(test_cbuf);
    elements_in_cbuf = circular_buf_size(test_cbuf);

    TEST_ASSERT_EQUAL_size_t(size, elements_in_cbuf);
}

TEST(CircularBuffer, CallToSizeFuncWhenTailGreaterThanHead)
{

    //tail will equal 2, and head = 0
    circular_buf_put(test_cbuf, data[0]);
    circular_buf_put(test_cbuf, data[1]);

    elements_in_cbuf = circular_buf_size(test_cbuf);

    TEST_ASSERT_EQUAL_size_t(2, elements_in_cbuf);
}

TEST(CircularBuffer, CallToSizeFuncWhenTailLessThanHead)
{
    uint8_t temp;
    //1 overwrite will occur, tail will = 1 and head = 1: full flag is set
    fill_buffer_num_elements(test_cbuf, size + 1);
    //make two reads so tail = 1 and head = 3: full flag no longer set
    circular_buf_get(test_cbuf, &temp);
    circular_buf_get(test_cbuf, &temp);


    elements_in_cbuf = circular_buf_size(test_cbuf);

    TEST_ASSERT_EQUAL_size_t(3, elements_in_cbuf);
}
//************* end tests *************//