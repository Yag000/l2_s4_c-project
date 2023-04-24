#ifndef TEST_CORE_H
#define TEST_CORE_H

#include <time.h>
#include <stdbool.h>

extern bool debug;

// Structure to hold test information.
typedef struct test_info
{
    int passed;
    int failed;
    int total;
    double time;
} test_info;

test_info *create_test_info();
void destroy_test_info(test_info *);
void print_test_info(const test_info *);

// Test utils
double clock_ticks_to_seconds(clock_t);

void print_test_header(const char *name);
void print_test_footer(const char *name);
void print_test_name(const char *name);

void handle_string_test(const char *expected, const char *actual, int line, const char *file, test_info *info);
void handle_boolean_test(bool expected, bool actual, int line, const char *file, test_info *info);

// All the tests
test_info *test_string_utils();
test_info *test_tree_dir_core();
test_info *test_parser();
test_info *test_pwd();

#endif