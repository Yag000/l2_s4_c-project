#include <stdio.h>
#include <stdlib.h>

#include "test_core.h"

test_info *create_test_info()
{
    test_info *info = malloc(sizeof(test_info));
    info->passed = 0;
    info->failed = 0;
    info->total = 0;
    info->time = 0;

    return info;
}

void destroy_test_info(test_info *info)
{
    free(info);
}

void print_test_info(test_info *info)
{
    printf("passed: %d, failed: %d, total: %d, time: %f seconds\n", info->passed, info->failed, info->total, info->time);
}
