#ifndef TEST_CORE_H
#define TEST_CORE_H

#include <time.h>
#include <stdbool.h>

extern bool debug;
extern char *out_stream_path;

/*
Structure to hold test information.
*/
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

void print_test_header(const char *);
void print_test_footer(const char *, const test_info *);
void print_test_name(const char *);

void handle_string_test(const char *, const char *, int, const char *, test_info *);
void handle_boolean_test(bool, bool, int, const char *, test_info *);
void handle_int_test(int, int, int, const char *, test_info *);

// All the tests
test_info *test_string_utils();
test_info *test_tree_dir_core();
test_info *test_parser();
test_info *test_command();
test_info *test_pwd();
test_info *test_mkdir();
test_info *test_print();
test_info *test_cp();

#endif