#include <stdio.h>
#include <stdlib.h>

#include "test_core.h"
#include "../main/command.h"
#include "../main/tree_dir_core.h"

static void test_pwd_function(test_info *info);

test_info *test_pwd()
{
    print_test_header("pwd");

    clock_t before = clock();
    // Create the test info
    test_info *info = create_test_info();

    // Add tests here
    test_pwd_function(info);
    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("pwd", info);
    return info;
}

static void test_pwd_function(test_info *info)
{
    // TODO
}
