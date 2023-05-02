#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../main/command.h"
#include "../main/constants.h"
#include "../main/file_manager.h"
#include "../main/string_utils.h"
#include "../main/tree_dir_core.h"
#include "test_core.h"

static void test_mv_function(test_info *);
static void test_command_mv_with_tree(test_info *);
static void test_error_of_mv(test_info *);

test_info *test_mv()
{
    // Create the test info
    print_test_header("mv");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    test_mv_function(info);
    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("mv", info);
    return info;
}

static void test_mv_function(test_info *info)
{
    test_command_mv_with_tree(info);
    test_error_of_mv(info);

    out_stream = stdout;
    out_stream_path = NULL;

    current_node = NULL;
}

static void test_command_mv_with_tree(test_info *info)
{
    current_node = create_basic_testing_tree();

    print_test_name("Testing mv with a tree");

    out_stream_path = "src/test/output/test_mv.txt";
    out_stream = open_file(out_stream_path, "w");

    char **tab_command = malloc(0);
    assert(tab_command != NULL);
    command *cmd_print = create_command(get_alloc_pointer_of_string("print"), 0, tab_command);

    tab_command = malloc(2 * (sizeof(char *)));
    assert(tab_command != NULL);
    command *cmd_mv = create_command(get_alloc_pointer_of_string("mv"), 2, tab_command);

    execute_command(cmd_print);

    tab_command[0] = "/test/test5";
    tab_command[1] = "/test11/test5";

    handle_boolean_test(true, execute_command(cmd_mv) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = "/test";
    tab_command[1] = "/test11/test1";

    handle_boolean_test(true, execute_command(cmd_mv) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = "/test11/test1/test9";
    tab_command[1] = "/test34";

    handle_boolean_test(true, execute_command(cmd_mv) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = "/test11";
    tab_command[1] = "/NomChange11";

    handle_boolean_test(true, execute_command(cmd_mv) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = get_alloc_pointer_of_string("/NomChange11");
    tab_command[1] = get_alloc_pointer_of_string("/test12/END");

    handle_boolean_test(true, execute_command(cmd_mv) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    destroy_command(cmd_mv);
    destroy_command(cmd_print);

    close_file(out_stream, out_stream_path);

    destroy_tree();
}

static void test_error_of_mv(test_info *info)
{
    current_node = create_basic_testing_tree();

    print_test_name("Testing mv errors");

    out_stream_path = "src/test/output/test_mv_error.txt";
    out_stream = open_file(out_stream_path, "w");

    char **tab_command = malloc(2 * (sizeof(char *)));
    assert(tab_command != NULL);
    command *cmd = create_command(get_alloc_pointer_of_string("mv"), 2, tab_command);

    tab_command[0] = "test/test5/";
    tab_command[1] = "/test11/test5";

    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "test13";
    tab_command[1] = "/test11/test5";

    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "test/test5/test";
    tab_command[1] = "/test11/test5";

    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "test/test5";
    tab_command[1] = "/test11/test5/";

    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "/test/test5";
    tab_command[1] = "/test11/test8/test11";

    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "/test/test5";
    tab_command[1] = "/test11/test10/test11";

    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "/test/test5";
    tab_command[1] = "/testt/test5";

    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "/test/test5";
    tab_command[1] = "/testt/test5";

    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "/test";
    tab_command[1] = "/test/test5/New";

    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = "/test11";
    tab_command[1] = "/test11/new";

    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = "/test/test5";
    tab_command[1] = "/test/test5/New";

    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = ".";
    tab_command[1] = "/test/test5/New";

    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    current_node = search_node_in_tree(current_node, "test/test5");

    tab_command[0] = "/test";
    tab_command[1] = "/test11/New";

    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = "/test/test5";
    tab_command[1] = "/test/test11/New";

    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    current_node = current_node->racine;

    tab_command[0] = "/test/test5";
    tab_command[1] = "/test/test5";

    handle_boolean_test(true, execute_command(cmd) == FATAL_ERROR, __LINE__, __FILE__, info);

    tab_command[0] = get_alloc_pointer_of_string("/test/test5");
    tab_command[1] = get_alloc_pointer_of_string("/test");

    handle_boolean_test(true, execute_command(cmd) == FATAL_ERROR, __LINE__, __FILE__, info);

    destroy_command(cmd);

    tab_command = malloc(0);
    assert(tab_command != NULL);
    cmd = create_command(get_alloc_pointer_of_string("mv"), 0, tab_command);
    handle_boolean_test(true, execute_command(cmd) == INVALID_NUMBER_OF_ARGS, __LINE__, __FILE__, info);

    destroy_command(cmd);

    tab_command = malloc(sizeof(char *) * 3);
    assert(tab_command != NULL);
    tab_command[0] = get_alloc_pointer_of_string("test");
    tab_command[1] = get_alloc_pointer_of_string("test");
    tab_command[2] = get_alloc_pointer_of_string("test");
    cmd = create_command(get_alloc_pointer_of_string("mv"), 3, tab_command);
    handle_boolean_test(true, execute_command(cmd) == INVALID_NUMBER_OF_ARGS, __LINE__, __FILE__, info);

    destroy_command(cmd);

    close_file(out_stream, out_stream_path);

    destroy_tree();
}