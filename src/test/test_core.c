#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "test_core.h"

// Create a new test info
test_info *create_test_info()
{
    test_info *info = malloc(sizeof(test_info));
    assert(info != NULL);
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
void print_test_info(const test_info *info)
{
    printf("passed: %d, failed: %d, total: %d, time: %f seconds\n", info->passed, info->failed, info->total, info->time);
}

double clock_ticks_to_seconds(clock_t ticks)
{
    return (double)ticks / CLOCKS_PER_SEC;
}

void print_test_header(const char *name)
{
    if (debug)
    {
        printf("\n----------------------- Testing %s -----------------------\n", name);
    }
}

void print_test_footer(const char *name)
{
    if (debug)
    {
        printf("\n----------------------- End test %s -----------------------\n", name);
    }
}

void print_test_name(const char *name)
{
    if (debug)
    {
        printf("\n->%s\n", name);
    }
}

void handle_string_test(const char *expected, const char *actual, int line, const char *file, test_info *info)
{
    if (strcmp(expected, actual) != 0)
    {
        printf("Error: %s != %s at line %d in file %s \n", actual, expected, line, file);
        info->failed++;
    }
    else
    {
        if (debug)
        {
            printf("Passed: %s == %s at line %d in file %s \n", actual, expected, line, file);
        }
        info->passed++;
    }

    info->total++;
}

void handle_boolean_test(bool expected, bool actual, int line, const char *file, test_info *info)
{
    if (expected != actual)
    {
        printf("Error: %d != %d at line %d in file %s \n", actual, expected, line, file);
        info->failed++;
    }
    else
    {
        if (debug)
        {
            printf("Passed: %d == %d at line %d in file %s \n", actual, expected, line, file);
        }
        info->passed++;
    }

    info->total++;
}