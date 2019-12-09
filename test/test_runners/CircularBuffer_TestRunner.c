#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(CircularBuffer)
{
	RUN_TEST_CASE(CircularBuffer, InitCbuf);
	RUN_TEST_CASE(CircularBuffer, CircularBufferEmptyOnInit);
	RUN_TEST_CASE(CircularBuffer, UserBufferSizeLessThanOneProducesError);
	RUN_TEST_CASE(CircularBuffer, AddFirstDataElementToCircularBuffer);
	RUN_TEST_CASE(CircularBuffer, CapacityMethodReturnsCorrectValue);
	RUN_TEST_CASE(CircularBuffer, AddMultipleDataElementsToCircularBuffer);
	RUN_TEST_CASE(CircularBuffer, CbufFullFunctionReturnsTrueWhenFull);
}