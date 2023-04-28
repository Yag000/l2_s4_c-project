#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "test_core.h"
#include "../main/command.h"
#include "../main/constants.h"
#include "../main/tree_dir_core.h"
#include "../main/file_manager.h"
#include "../main/string_utils.h"

static void test_print_function(test_info *);
static void *test_print_while_creating_tree(test_info *info);
static void invalid_name_format_test_handler(test_info *info);

test_info *test_print()
{
    print_test_header("print");

    clock_t before = clock();
    // Create the test info
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

    out_stream_path = "src/test/output/test_print.txt";
    out_stream = open_file(out_stream_path, "w");

    printf("test\n");

    test_print_while_creating_tree(info);
    printf("test\n");
    invalid_name_format_test_handler(info);

    printf("test\n");
    close_file(out_stream, out_stream_path);
    printf("test\n");

    out_stream = stdin;
    out_stream_path = NULL;

    current_node = NULL;
}

static void *test_print_while_creating_tree(test_info *info)
{
    char **tab_command = malloc(0);
    assert(tab_command != NULL);
    command *cmd = create_command(get_alloc_pointer_of_string("print"), 0, tab_command);

    noeud *root = create_root_noeud();
    current_node = root;

    handle_boolean_test(true, execute_command(cmd) == 0, __LINE__, __FILE__, info);

    noeud *node1 = create_noeud(true, "test", root);
    append_a_fils_to_noeud(root, node1);

    append_a_fils_to_noeud(node1, create_noeud(false, "test2", node1));
    append_a_fils_to_noeud(node1, create_noeud(true, "test3", node1));
    append_a_fils_to_noeud(node1, create_noeud(false, "test4", node1));

    noeud *node2 = create_noeud(true, "test5", node1);
    append_a_fils_to_noeud(node1, node2);

    handle_boolean_test(true, execute_command(cmd) == 0, __LINE__, __FILE__, info);

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

    handle_boolean_test(true, execute_command(cmd) == 0, __LINE__, __FILE__, info);

    destroy_command(cmd);
    destroy_noeud(root);

    return root;
}

static void invalid_name_format_test_handler(test_info *info)
{
    char **tab_command = malloc(sizeof(char *));
    assert(tab_command != NULL);
    tab_command[0] = get_alloc_pointer_of_string("test");
    command *cmd = create_command(get_alloc_pointer_of_string("print"), 1, tab_command);
    handle_boolean_test(true, execute_command(cmd) == 1, __LINE__, __FILE__, info);
    destroy_command(cmd);

    tab_command = malloc(sizeof(char *) * 2);
    assert(tab_command != NULL);
    tab_command[0] = get_alloc_pointer_of_string("test");
    tab_command[1] = get_alloc_pointer_of_string("test");
    cmd = create_command(get_alloc_pointer_of_string("print"), 2, tab_command);
    handle_boolean_test(true, execute_command(cmd) == 1, __LINE__, __FILE__, info);

    destroy_command(cmd);
}