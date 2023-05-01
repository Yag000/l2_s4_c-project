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
static void test_command_cp_with_tree(test_info *);
static void test_error_of_cp(test_info *);

test_info *test_cp()
{
    // Create the test info
    print_test_header("cp");
    clock_t before = clock();
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
    test_error_of_cp(info);

    out_stream = stdout;
    out_stream_path = NULL;

    current_node = NULL;
}

static void test_command_cp_with_tree(test_info *info)
{
    print_test_name("Testing cp with a tree");

    out_stream_path = "src/test/output/test_cp.txt";
    out_stream = open_file(out_stream_path, "w");

    char **tab_command = malloc(0);
    assert(tab_command != NULL);
    command *cmd_print = create_command(get_alloc_pointer_of_string("print"), 0, tab_command);

    tab_command = malloc(2 * (sizeof(char *)));
    assert(tab_command != NULL);
    command *cmd_cp = create_command(get_alloc_pointer_of_string("cp"), 2, tab_command);

    current_node = create_basic_testing_tree();
    current_node = search_node_in_tree(current_node, "test11");

    execute_command(cmd_print);

    tab_command[0] = "/test/test5";
    tab_command[1] = "./test";
    handle_boolean_test(true, execute_command(cmd_cp) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = "/test/test5/test6";
    tab_command[1] = "./test12";
    handle_boolean_test(true, execute_command(cmd_cp) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = "/test12";
    tab_command[1] = "../test/test5/check";
    handle_boolean_test(true, execute_command(cmd_cp) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = "/test";
    tab_command[1] = "/test12/check2";
    handle_boolean_test(true, execute_command(cmd_cp) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = get_alloc_pointer_of_string("/test12/check2");
    tab_command[1] = get_alloc_pointer_of_string("/test12/check3");
    handle_boolean_test(true, execute_command(cmd_cp) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    destroy_command(cmd_print);
    destroy_command(cmd_cp);

    destroy_tree();

    close_file(out_stream, out_stream_path);
}

static void test_error_of_cp(test_info *info)
{
    print_test_name("Testing cp errors");

    out_stream_path = "src/test/output/test_cp_error.txt";
    out_stream = open_file(out_stream_path, "w");

    current_node = create_basic_testing_tree();

    char **tab_command = malloc(2 * (sizeof(char *)));
    assert(tab_command != NULL);
    command *cmd = create_command(get_alloc_pointer_of_string("cp"), 2, tab_command);

    tab_command[0] = "/test/test";
    tab_command[1] = "/test/nouveau";
    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "/test/test5/tes4";
    tab_command[1] = "/test/nouveau";
    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "/test";
    tab_command[1] = ".";
    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "/test";
    tab_command[1] = "../../.";
    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "/test";
    tab_command[1] = "test12/test3/test";
    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "/test";
    tab_command[1] = "/test/nouveau";
    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = "/test12";
    tab_command[1] = "/test12/test";
    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = "/test/test5/test7";
    tab_command[1] = "/test/test5/test7/nouveau";
    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = ".";
    tab_command[1] = "test12/nouveau";
    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = "/test/test5";
    tab_command[1] = "/test";
    handle_boolean_test(true, execute_command(cmd) == FATAL_ERROR, __LINE__, __FILE__, info);

    tab_command[0] = "/test12/test13";
    tab_command[1] = "/test/test2";
    handle_boolean_test(true, execute_command(cmd) == FATAL_ERROR, __LINE__, __FILE__, info);

    tab_command[0] = get_alloc_pointer_of_string("/test/test5/test6");
    tab_command[1] = get_alloc_pointer_of_string("/test12");
    handle_boolean_test(true, execute_command(cmd) == FATAL_ERROR, __LINE__, __FILE__, info);

    destroy_command(cmd);

    tab_command = malloc(0);
    assert(tab_command != NULL);
    cmd = create_command(get_alloc_pointer_of_string("rm"), 0, tab_command);
    handle_boolean_test(true, execute_command(cmd) == INVALID_NUMBER_OF_ARGS, __LINE__, __FILE__, info);

    destroy_command(cmd);

    tab_command = malloc(sizeof(char *) * 3);
    assert(tab_command != NULL);
    tab_command[0] = get_alloc_pointer_of_string("test");
    tab_command[1] = get_alloc_pointer_of_string("test");
    tab_command[2] = get_alloc_pointer_of_string("test");
    cmd = create_command(get_alloc_pointer_of_string("cp"), 3, tab_command);
    handle_boolean_test(true, execute_command(cmd) == INVALID_NUMBER_OF_ARGS, __LINE__, __FILE__, info);

    destroy_command(cmd);
    destroy_tree();

    close_file(out_stream, out_stream_path);
}