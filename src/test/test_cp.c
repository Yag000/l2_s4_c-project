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
static noeud *create_tree_to_test_for_cp();
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

static noeud *create_tree_to_test_for_cp()
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

static void test_command_cp_with_tree(test_info *info)
{
    out_stream_path = "src/test/output/test_cp.txt";
    out_stream = open_file(out_stream_path, "w");

    char **tab_command = malloc(0);
    assert(tab_command != NULL);
    command *cmd_print = create_command(get_alloc_pointer_of_string("print"), 0, tab_command);

    tab_command = malloc(2 * (sizeof(char *)));
    tab_command[0] = get_alloc_pointer_of_string("/");
    tab_command[1] = get_alloc_pointer_of_string("/");
    assert(tab_command != NULL);
    command *cmd_cp = create_command(get_alloc_pointer_of_string("cp"), 2, tab_command);

    current_node = create_tree_to_test_for_cp();
    current_node = search_node_in_tree(current_node, "test11");

    handle_boolean_test(true, execute_command(cmd_print) == SUCCESS, __LINE__, __FILE__, info);

    tab_command[0] = get_alloc_pointer_of_string("/test/test5");
    tab_command[1] = get_alloc_pointer_of_string("./test");
    handle_boolean_test(true, execute_command(cmd_cp) == SUCCESS, __LINE__, __FILE__, info);
    execute_command(cmd_print);

    handle_boolean_test(true, execute_command(cmd_print) == SUCCESS, __LINE__, __FILE__, info);
    destroy_command(cmd_print);
    destroy_command(cmd_cp);

    destroy_tree();

    close_file(out_stream, out_stream_path);
}