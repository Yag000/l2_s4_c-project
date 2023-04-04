#ifndef TEST_CORE_H

#define TEST_CORE_H

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

#endif