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

void print_test_header(char *name)
{
    if (verbose)
    {
        printf("\n----------------------- Testing %s -----------------------\n", name);
    }
}

void print_test_footer(char *name)
{
    if (verbose)
    {

        printf("\n----------------------- End test %s -----------------------\n", name);
    }
}

void handle_string_test(char *expected, char *actual, int line, char *file, test_info *info)
{
    if (strcmp(expected, actual) != 0)
    {
        printf("Error: %s != %s at line %d in file %s \n", actual, expected, line, file);
        info->failed++;
    }
    else
    {
        if (verbose)
        {
            printf("Passed: %s == %s at line %d in file %s \n", actual, expected, line, file);
        }
        info->passed++;
    }

    info->total++;
}

void handle_boolean_test(bool expected, bool actual, int line, char *file, test_info *info)
{
    if (expected != actual)
    {
        printf("Error: %d != %d at line %d in file %s \n", actual, expected, line, file);
        info->failed++;
    }
    else
    {
        if (verbose)
        {
            printf("Passed: %d == %d at line %d in file %s \n", actual, expected, line, file);
        }
        info->passed++;
    }

    info->total++;
}