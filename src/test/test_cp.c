#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../main/command.h"
#include "../main/constants.h"
#include "../main/file_manager.h"
#include "../main/string_utils.h"
#include "../main/tree_dir_core.h"
#include "test_core.h"

static void test_cp_function(test_info *);
static void test_command_cp_with_tree(test_info *info);

test_info *test_cp()
{
    print_test_header("cp");

    clock_t before = clock();
    // Create the test info
    test_info *info = create_test_info();

    // Add tests here
    test_cp_function(info);
    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("cp", info);
    return info;
}

static void test_cp_function(test_info *info)
{
    test_command_cp_with_tree(info);
}

static void test_command_cp_with_tree(test_info *info)
{
    out_stream_path = "src/test/output/test_cp.txt";
    out_stream = open_file(out_stream_path, "w");

    char **tab_command = malloc(0);
    assert(tab_command != NULL);
    command *cmd_print = create_command(get_alloc_pointer_of_string("print"), 0, tab_command);

    tab_command = malloc(2 * (sizeof(char *)));
    assert(tab_command != NULL);
    command *cmd_cp = create_command(get_alloc_pointer_of_string("cp"), 2, tab_command);

    current_node = create_tree_to_test();
    current_node = search_node_in_tree(current_node, "test11");

    handle_boolean_test(true, execute_command(cmd_print) == SUCCESS, __LINE__, __FILE__, info);

    tab_command[0] = get_alloc_pointer_of_string("/test/test5");
    tab_command[1] = get_alloc_pointer_of_string("./test");
    handle_boolean_test(true, execute_command(cmd_cp) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = get_alloc_pointer_of_string("/test/test5/test6");
    tab_command[1] = get_alloc_pointer_of_string("./test12");
    handle_boolean_test(true, execute_command(cmd_cp) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = get_alloc_pointer_of_string("/test12");
    tab_command[1] = get_alloc_pointer_of_string("../test/test5/check");
    handle_boolean_test(true, execute_command(cmd_cp) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = get_alloc_pointer_of_string("/test");
    tab_command[1] = get_alloc_pointer_of_string("/test12/lastCheck");
    handle_boolean_test(true, execute_command(cmd_cp) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    destroy_command(cmd_print);
    destroy_command(cmd_cp);

    destroy_tree();

    close_file(out_stream, out_stream_path);
}