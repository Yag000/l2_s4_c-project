#include "test_utils.h"

// Converts a clock_t value to seconds
double clock_ticks_to_seconds(clock_t ticks)
{
    return (double)ticks / CLOCKS_PER_SEC;
}