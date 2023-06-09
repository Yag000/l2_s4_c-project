#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../main/command.h"
#include "../main/constants.h"
#include "../main/file_manager.h"
#include "../main/string_utils.h"
#include "../main/tree_dir_core.h"
#include "test_core.h"

static void test_print_function(test_info *);
static void test_print_while_creating_tree(test_info *);
static void test_illegal_number_of_args_of_print(test_info *);

test_info *test_print()
{
    // Test setup
    print_test_header("print");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    test_print_function(info);

    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("print", info);
    return info;
}

static void test_print_function(test_info *info)
{
    print_test_name("Testing command print");

    test_print_while_creating_tree(info);
    test_illegal_number_of_args_of_print(info);

    out_stream = stdout;
    out_stream_path = NULL;

    current_node = NULL;
}

static void test_print_while_creating_tree(test_info *info)
{
    out_stream_path = "src/resources/unit_tests/output/test_print_display.txt";
    out_stream = open_file(out_stream_path, "w");

    char **tab_command = malloc(0);
    assert(tab_command != NULL);
    command *cmd = create_command(get_alloc_pointer_of_string("print"), 0, tab_command);

    node *root = create_root_node();
    current_node = root;

    handle_boolean_test(true, execute_command(cmd) == SUCCESS, __LINE__, __FILE__, info);

    node *node1 = create_node(true, "test", root);
    append_child_to_node(root, node1);

    append_child_to_node(node1, create_node(false, "test2", node1));
    append_child_to_node(node1, create_node(true, "test3", node1));
    append_child_to_node(node1, create_node(false, "test4", node1));

    node *node2 = create_node(true, "test5", node1);
    append_child_to_node(node1, node2);

    handle_boolean_test(true, execute_command(cmd) == SUCCESS, __LINE__, __FILE__, info);

    append_child_to_node(node2, create_node(false, "test6", node2));
    append_child_to_node(node2, create_node(true, "test7", node2));
    append_child_to_node(node2, create_node(false, "test8", node2));

    append_child_to_node(node1, create_node(false, "test9", node2));
    append_child_to_node(root, create_node(false, "test10", root));
    append_child_to_node(root, create_node(true, "test11", root));

    node1 = create_node(true, "test12", root);

    append_child_to_node(root, node1);
    append_child_to_node(node1, create_node(false, "test13", node1));
    append_child_to_node(node1, create_node(false, "test14", node1));
    append_child_to_node(node1, create_node(false, "test15", node1));

    handle_boolean_test(true, execute_command(cmd) == SUCCESS, __LINE__, __FILE__, info);

    destroy_command(cmd);
    destroy_node(root);

    close_file(out_stream, out_stream_path);
}

static void test_illegal_number_of_args_of_print(test_info *info)
{
    current_node = create_root_node();
    out_stream_path = "src/resources/unit_tests/output/test_print_illegal_number_of_args.txt";
    out_stream = open_file(out_stream_path, "w");

    char **tab_command = malloc(sizeof(char *));
    assert(tab_command != NULL);
    tab_command[0] = get_alloc_pointer_of_string("test");
    command *cmd = create_command(get_alloc_pointer_of_string("print"), 1, tab_command);
    handle_boolean_test(true, execute_command(cmd) == INVALID_NUMBER_OF_ARGS, __LINE__, __FILE__, info);
    destroy_command(cmd);

    tab_command = malloc(sizeof(char *) * 2);
    assert(tab_command != NULL);
    tab_command[0] = get_alloc_pointer_of_string("test");
    tab_command[1] = get_alloc_pointer_of_string("test");
    cmd = create_command(get_alloc_pointer_of_string("print"), 2, tab_command);
    handle_boolean_test(true, execute_command(cmd) == INVALID_NUMBER_OF_ARGS, __LINE__, __FILE__, info);

    destroy_command(cmd);
    destroy_node(current_node);

    close_file(out_stream, out_stream_path);
}
