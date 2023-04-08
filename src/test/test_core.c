#include <stdio.h>
#include <stdlib.h>

#include "test_core.h"

// Create a new test info
test_info *create_test_info()
{
    test_info *info = malloc(sizeof(test_info));
    info->passed = 0;
    info->failed = 0;
    info->total = 0;
    info->time = 0;

    return info;
}

// Destroy the test info
void destroy_test_info(test_info *info)
{
    free(info);
}

// Print the test info
void print_test_info(test_info *info)
{
    printf("passed: %d, failed: %d, total: %d, time: %f seconds\n", info->passed, info->failed, info->total, info->time);
}

double clock_ticks_to_seconds(clock_t ticks)
{
    return (double)ticks / CLOCKS_PER_SEC;
}
