#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../main/command.h"
#include "../main/constants.h"
#include "../main/file_manager.h"
#include "../main/string_utils.h"
#include "../main/tree_dir_core.h"
#include "test_core.h"

static void test_rm_function(test_info *);
static noeud *create_tree_to_test_for_rm();
static void test_command_rm_with_tree(test_info *);
static void test_error_of_rm(test_info *);

test_info *test_rm()
{
    // Create the test info
    print_test_header("rm");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    test_rm_function(info);
    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("rm", info);
    return info;
}

static void test_rm_function(test_info *info)
{
    test_command_rm_with_tree(info);
    test_error_of_rm(info);

    out_stream = stdin;
    out_stream_path = NULL;

    current_node = NULL;
}

static noeud *create_tree_to_test_for_rm()
{
    noeud *root = create_root_noeud();

    noeud *node1 = create_noeud(true, "test", root);
    append_a_fils_to_noeud(root, node1);

    append_a_fils_to_noeud(node1, create_noeud(false, "test2", node1));
    append_a_fils_to_noeud(node1, create_noeud(true, "test3", node1));
    append_a_fils_to_noeud(node1, create_noeud(false, "test4", node1));

    noeud *node2 = create_noeud(true, "test5", node1);
    append_a_fils_to_noeud(node1, node2);

    append_a_fils_to_noeud(node2, create_noeud(false, "test6", node2));
    append_a_fils_to_noeud(node2, create_noeud(true, "test7", node2));
    append_a_fils_to_noeud(node2, create_noeud(false, "test8", node2));

    append_a_fils_to_noeud(node1, create_noeud(false, "test9", node2));
    append_a_fils_to_noeud(root, create_noeud(false, "test10", root));
    append_a_fils_to_noeud(root, create_noeud(true, "test11", root));

    node1 = create_noeud(true, "test12", root);

    append_a_fils_to_noeud(root, node1);
    append_a_fils_to_noeud(node1, create_noeud(false, "test13", node1));
    append_a_fils_to_noeud(node1, create_noeud(false, "test14", node1));
    append_a_fils_to_noeud(node1, create_noeud(false, "test15", node1));

    return root;
}

static void test_command_rm_with_tree(test_info *info)
{
    print_test_name("Testing rm with a tree");

    out_stream_path = "src/test/output/test_rm.txt";
    out_stream = open_file(out_stream_path, "w");

    char **tab_command = malloc(0);
    assert(tab_command != NULL);
    command *cmd_print = create_command(get_alloc_pointer_of_string("print"), 0, tab_command);

    tab_command = malloc(sizeof(char *));
    assert(tab_command != NULL);
    command *cmd_rm = create_command(get_alloc_pointer_of_string("rm"), 1, tab_command);

    current_node = create_tree_to_test_for_rm();
    current_node = search_node_in_tree(current_node, "test11");

    execute_command(cmd_print);

    tab_command[0] = "/test/test5";
    handle_boolean_test(true, execute_command(cmd_rm) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = "/test/";
    handle_boolean_test(true, execute_command(cmd_rm) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = "/test12/";
    handle_boolean_test(true, execute_command(cmd_rm) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    destroy_tree();

    current_node = create_tree_to_test_for_rm();

    execute_command(cmd_print);

    tab_command[0] = "test12/test15";
    handle_boolean_test(true, execute_command(cmd_rm) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = "test12";
    handle_boolean_test(true, execute_command(cmd_rm) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = "test/test2";
    handle_boolean_test(true, execute_command(cmd_rm) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = "test/test3";
    handle_boolean_test(true, execute_command(cmd_rm) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    current_node = search_node_in_tree(current_node, "test");

    tab_command[0] = "../test10";
    handle_boolean_test(true, execute_command(cmd_rm) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    tab_command[0] = "../test11";
    handle_boolean_test(true, execute_command(cmd_rm) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    current_node = current_node->racine;

    tab_command[0] = get_alloc_pointer_of_string("test");
    handle_boolean_test(true, execute_command(cmd_rm) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    destroy_command(cmd_rm);
    destroy_command(cmd_print);

    destroy_tree();

    close_file(out_stream, out_stream_path);
}

static void test_error_of_rm(test_info *info)
{
    print_test_name("Testing rm errors");

    current_node = create_tree_to_test_for_rm();

    out_stream_path = "src/test/output/test_rm_error.txt";
    out_stream = open_file(out_stream_path, "w");

    char **tab_command = malloc(sizeof(char *));
    assert(tab_command != NULL);
    command *cmd = create_command(get_alloc_pointer_of_string("rm"), 1, tab_command);

    tab_command[0] = "/";
    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = "./";
    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    current_node = search_node_in_tree(current_node, "test/test5");

    tab_command[0] = "/test/test5";
    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = "/test/";
    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = "./";
    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = "../";
    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = "../../";
    handle_boolean_test(true, execute_command(cmd) == INVALID_SELECTION, __LINE__, __FILE__, info);

    tab_command[0] = "test";
    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    tab_command[0] = get_alloc_pointer_of_string("../test4/");
    handle_boolean_test(true, execute_command(cmd) == INVALID_PATH, __LINE__, __FILE__, info);

    destroy_command(cmd);

    tab_command = malloc(0);
    assert(tab_command != NULL);
    cmd = create_command(get_alloc_pointer_of_string("rm"), 0, tab_command);
    handle_boolean_test(true, execute_command(cmd) == INVALID_NUMBER_OF_ARGS, __LINE__, __FILE__, info);

    destroy_command(cmd);

    tab_command = malloc(sizeof(char *) * 2);
    assert(tab_command != NULL);
    tab_command[0] = get_alloc_pointer_of_string("test");
    tab_command[1] = get_alloc_pointer_of_string("test");
    cmd = create_command(get_alloc_pointer_of_string("rm"), 2, tab_command);
    handle_boolean_test(true, execute_command(cmd) == INVALID_NUMBER_OF_ARGS, __LINE__, __FILE__, info);

    destroy_command(cmd);
    destroy_noeud(current_node->racine);

    close_file(out_stream, out_stream_path);
}