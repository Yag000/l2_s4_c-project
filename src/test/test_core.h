#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef TEST_CORE_H
#define TEST_CORE_H

extern bool verbose;

// Sructure to hold test information.
typedef struct test_info
{
    int passed;
    int failed;
    int total;
    double time;
} test_info;

test_info *create_test_info();
void destroy_test_info(test_info *);
void print_test_info(test_info *);

double clock_ticks_to_seconds(clock_t);

// All the tests
test_info *test_example();

#endif