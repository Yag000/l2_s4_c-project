#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../main/command.h"
#include "../main/constants.h"
#include "../main/file_manager.h"
#include "../main/string_utils.h"
#include "../main/tree_dir_core.h"
#include "test_core.h"

static void test_ls_function(test_info *);
static node *create_tree_and_test_ls_without_path_while(test_info *);
static void test_ls_with_path(test_info *, node *);
static void test_ls_error_with_path(test_info *, node *);
static void test_invalid_number_of_arg_of_ls(test_info *);

test_info *test_ls()
{
    // Test setup
    print_test_header("ls");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    test_ls_function(info);

    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("ls", info);
    return info;
}

static void test_ls_function(test_info *info)
{
    print_test_name("Testing command ls");

    node *root = create_tree_and_test_ls_without_path_while(info);

    test_ls_with_path(info, root);
    test_ls_error_with_path(info, root);
    test_invalid_number_of_arg_of_ls(info);

    destroy_node(root);

    out_stream = stdout;
    out_stream_path = NULL;

    current_node = NULL;
}

static node *create_tree_and_test_ls_without_path_while(test_info *info)
{
    print_test_name("Testing command ls without path ");

    out_stream_path = "src/resources/unit_tests/output/test_ls_without_path.txt";
    out_stream = open_file(out_stream_path, "w");

    char **tab_command = malloc(0);
    assert(tab_command != NULL);
    command *cmd = create_command(get_alloc_pointer_of_string("ls"), 0, tab_command);

    node *root = create_root_node();
    current_node = root;

    handle_boolean_test(true, execute_command(cmd) == SUCCESS, __LINE__, __FILE__, info);

    node *node1 = create_node(true, "test", root);
    append_child_to_node(root, node1);

    current_node = node1;

    append_child_to_node(node1, create_node(false, "test2", node1));
    handle_boolean_test(true, execute_command(cmd) == SUCCESS, __LINE__, __FILE__, info);

    append_child_to_node(node1, create_node(true, "test3", node1));
    handle_boolean_test(true, execute_command(cmd) == SUCCESS, __LINE__, __FILE__, info);

    append_child_to_node(node1, create_node(false, "test4", node1));
    handle_boolean_test(true, execute_command(cmd) == SUCCESS, __LINE__, __FILE__, info);

    node *node2 = create_node(true, "test5", node1);
    append_child_to_node(node1, node2);
    append_child_to_node(node2, create_node(false, "test6", node2));
    append_child_to_node(node2, create_node(true, "test7", node2));
    append_child_to_node(node2, create_node(false, "test8", node2));

    current_node = node2;
    handle_boolean_test(true, execute_command(cmd) == SUCCESS, __LINE__, __FILE__, info);

    append_child_to_node(root, create_node(false, "test9", root));
    append_child_to_node(root, create_node(true, "test10", root));

    node1 = create_node(true, "test11", root);
    append_child_to_node(root, node1);
    append_child_to_node(node1, create_node(false, "test12", node1));

    current_node = root;
    handle_boolean_test(true, execute_command(cmd) == SUCCESS, __LINE__, __FILE__, info);

    current_node = node1;
    handle_boolean_test(true, execute_command(cmd) == SUCCESS, __LINE__, __FILE__, info);

    destroy_command(cmd);

    close_file(out_stream, out_stream_path);

    return root;
}

static void test_ls_with_path(test_info *info, node *root)
{
    print_test_name("Testing command ls with path ");

    out_stream_path = "src/resources/unit_tests/output/test_ls_with_path.txt";
    out_stream = open_file(out_stream_path, "w");

    current_node = root;

    char **tab_command = malloc(sizeof(char *));
    assert(tab_command != NULL);
    command *cmd = create_command(get_alloc_pointer_of_string("ls"), 1, tab_command);

    tab_command[0] = "test/test5/../../test11";
    handle_boolean_test(true, execute_command(cmd) == SUCCESS, __LINE__, __FILE__, info);

    current_node = search_node_in_tree(root, "test11");

    tab_command[0] = "../test/test5";
    handle_boolean_test(true, execute_command(cmd) == SUCCESS, __LINE__, __FILE__, info);

    tab_command[0] = "..";
    handle_boolean_test(true, execute_command(cmd) == SUCCESS, __LINE__, __FILE__, info);

    tab_command[0] = "/test10";
    handle_boolean_test(true, execute_command(cmd) == SUCCESS, __LINE__, __FILE__, info);

    tab_command[0] = get_alloc_pointer_of_string("/test/test5");
    handle_boolean_test(true, execute_command(cmd) == SUCCESS, __LINE__, __FILE__, info);

    destroy_command(cmd);

    close_file(out_stream, out_stream_path);
}

static void test_ls_error_with_path(test_info *info, node *root)
{
    print_test_name("Testing command ls errors with path ");

    out_stream_path = "src/resources/unit_tests/output/test_ls_error_with_path.txt";
    out_stream = open_file(out_stream_path, "w");

    char **tab_command = malloc(sizeof(char *));
    assert(tab_command != NULL);
    command *cmd = create_command(get_alloc_pointer_of_string("ls"), 1, tab_command);

    current_node = root;

    tab_command[0] = "/test/";
    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "/test11/test9";
    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "/test5/test6";
    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "test4";
    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "test1";
    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = "test11/test12";
    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = "test/test4";
    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = "/test9";
    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = get_alloc_pointer_of_string("/test/test5/test6");
    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    destroy_command(cmd);

    close_file(out_stream, out_stream_path);
}

static void test_invalid_number_of_arg_of_ls(test_info *info)
{
    print_test_name("Testing command ls errors of invalid number of args ");

    out_stream_path = "src/resources/unit_tests/output/test_ls_invalid_number_of_args.txt";
    out_stream = open_file(out_stream_path, "w");

    char **tab_command = malloc(sizeof(char *) * 2);
    assert(tab_command != NULL);
    tab_command[0] = get_alloc_pointer_of_string("test");
    tab_command[1] = get_alloc_pointer_of_string("test");
    command *cmd = create_command(get_alloc_pointer_of_string("ls"), 2, tab_command);
    handle_boolean_test(true, execute_command(cmd) == INVALID_NUMBER_OF_ARGS, __LINE__, __FILE__, info);

    destroy_command(cmd);

    tab_command = malloc(sizeof(char *) * 3);
    assert(tab_command != NULL);
    tab_command[0] = get_alloc_pointer_of_string("test");
    tab_command[1] = get_alloc_pointer_of_string("test");
    tab_command[2] = get_alloc_pointer_of_string("test");

    cmd = create_command(get_alloc_pointer_of_string("ls"), 3, tab_command);
    handle_boolean_test(true, execute_command(cmd) == INVALID_NUMBER_OF_ARGS, __LINE__, __FILE__, info);

    destroy_command(cmd);

    close_file(out_stream, out_stream_path);
}
