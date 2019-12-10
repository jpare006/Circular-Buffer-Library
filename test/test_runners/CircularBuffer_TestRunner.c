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
	RUN_TEST_CASE(CircularBuffer, AddingTwoMoreElementsAfterFullOverwritesOldestElements);
	RUN_TEST_CASE(CircularBuffer, ResetFuncSetsCbufHeadAndTailBackToZeroAndFullToFalse);
	RUN_TEST_CASE(CircularBuffer, AddingMultipleElementsAfterFullContinuesToOverwriteOldestElements);
	RUN_TEST_CASE(CircularBuffer, GetElementFromCircularBuffer);
	RUN_TEST_CASE(CircularBuffer, GetTwoElementsFromCircularBuffer);
	RUN_TEST_CASE(CircularBuffer, HeadPointerIsUpdatedAfterOverwriteOccurs);
	RUN_TEST_CASE(CircularBuffer, FullFlagSetToZeroAfterReadOcurs);
}