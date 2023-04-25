#include <stdio.h>
#include <stdlib.h>

#include "test_core.h"
#include "../main/command.h"
#include "../main/tree_dir_core.h"

void test_pwd_function(test_info *info);
void test_get_absolute_path_of_node(test_info *info);
void test_get_number_of_node_in_absolute_path(test_info *info);

test_info *test_pwd()
{
    print_test_header("pwd");

    clock_t before = clock();
    // Create the test info
    test_info *info = create_test_info();

    // Add tests here
    // test_pwd_function(info);
    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    printf("Test pwd: ");
    print_test_info(info);
    print_test_footer("pwd");
    return info;
}

void test_pwd_function(test_info *info)
{
    // TODO
}
