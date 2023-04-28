#include <stdio.h>
#include <stdlib.h>

#include "test_core.h"
#include "../main/command.h"
#include "../main/constants.h"
#include "../main/tree_dir_core.h"
#include "../main/file_manager.h"
#include "../main/string_utils.h"

void test_ls_function(test_info *info);

test_info *test_ls()
{
    print_test_header("ls");

    clock_t before = clock();
    // Create the test info
    test_info *info = create_test_info();

    // Add tests here
    test_ls_function(info);
    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("ls", info);
    return info;
}

void test_ls_function(test_info *info)
{
    print_test_name("Testing command ls");

    out_stream_path = "src/test/output/test_ls.txt";
    out_stream = open_file(out_stream_path, "w");

    command *c = create_command(get_alloc_pointer_of_string("ls"), 0, malloc(0));

    noeud *root = create_root_noeud();
    current_node = root;

    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    noeud *node1 = create_noeud(true, "test", root);
    append_a_fils_to_noeud(root, node1);

    current_node = node1;

    append_a_fils_to_noeud(node1, create_noeud(false, "test2", node1));
    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    append_a_fils_to_noeud(node1, create_noeud(true, "test3", node1));
    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    append_a_fils_to_noeud(node1, create_noeud(false, "test4", node1));
    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    noeud *node2 = create_noeud(true, "test5", node1);
    append_a_fils_to_noeud(node1, node2);
    append_a_fils_to_noeud(node2, create_noeud(false, "test6", node2));
    append_a_fils_to_noeud(node2, create_noeud(true, "test7", node2));
    append_a_fils_to_noeud(node2, create_noeud(false, "test8", node2));

    current_node = node2;
    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    append_a_fils_to_noeud(root, create_noeud(false, "test9", root));
    append_a_fils_to_noeud(root, create_noeud(true, "test10", root));

    node1 = create_noeud(true, "test11", root);
    append_a_fils_to_noeud(root, node1);
    append_a_fils_to_noeud(node1, create_noeud(false, "test12", node1));

    current_node = root;
    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    current_node = node1;
    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    destroy_command(c);

    char **tab_command = malloc(sizeof(char *));
    c = create_command(get_alloc_pointer_of_string("ls"), 1, tab_command);

    current_node = root;

    tab_command[0] = "test/test5/../../test11";
    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    current_node = node1;

    tab_command[0] = "../test/test5";
    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    tab_command[0] = "../";
    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    tab_command[0] = "test4";
    handle_boolean_test(true, execute_command(c) == 1, __LINE__, __FILE__, info);

    tab_command[0] = get_alloc_pointer_of_string("test12");
    handle_boolean_test(true, execute_command(c) == 1, __LINE__, __FILE__, info);

    destroy_command(c);

    tab_command = malloc(sizeof(char *) * 2);
    tab_command[0] = get_alloc_pointer_of_string("test");
    tab_command[1] = get_alloc_pointer_of_string("test");
    c = create_command(get_alloc_pointer_of_string("ls"), 2, tab_command);
    handle_boolean_test(true, execute_command(c) == 1, __LINE__, __FILE__, info);

    destroy_command(c);
    destroy_noeud(root);

    close_file(out_stream, out_stream_path);
    out_stream = stdin;
    out_stream_path = NULL;
}