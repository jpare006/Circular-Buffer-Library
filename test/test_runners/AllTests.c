#include "unity_fixture.h"

static void RunAllTests(void)
{
    RUN_TEST_GROUP(CircularBuffer);
}

int main(int argc, const char * argv[])
{
    UnityMain(argc, argv, RunAllTests);
}