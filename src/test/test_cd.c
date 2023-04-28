#include "test_core.h"

#include "../main/command.h"

void test_go_to_root(test_info *);
void test_go_to_previous_directory(test_info *);
void test_invalid_invalid_number_args(test_info *);
void test_invalid_path(test_info *);
void test_valid_paths(test_info *);

test_info *test_cd()
{
    // Test setup
    print_test_header("cd");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    test_go_to_root(info);
    test_go_to_previous_directory(info);
    test_invalid_path(info);
    test_valid_paths(info);

    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("cd", info);
    return info;
}

void test_go_to_root(test_info *info){}
void test_go_to_previous_directory(test_info *info){}
void test_invalid_invalid_number_args(test_info *info){}
void test_invalid_path(test_info *info){}
void test_valid_paths(test_info *info){}
