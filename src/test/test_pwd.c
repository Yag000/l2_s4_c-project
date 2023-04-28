#include <stdio.h>
#include <stdlib.h>

#include "test_core.h"
#include "../main/command.h"
#include "../main/constants.h"
#include "../main/tree_dir_core.h"
#include "../main/file_manager.h"
#include "../main/string_utils.h"

static void test_pwd_function(test_info *);

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
    print_test_name("Testing command pwd");

    out_stream_path = "src/test/output/test_pwd.txt";
    out_stream = open_file(out_stream_path, "w");

    command *c = create_command(get_alloc_pointer_of_string("pwd"), 0, malloc(0));

    noeud *root = create_root_noeud();
    current_node = root;

    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    noeud *node = create_noeud(true, "test", root);
    append_a_fils_to_noeud(root, node);
    current_node = node;

    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    node = create_noeud(true, "test2", current_node);
    append_a_fils_to_noeud(current_node, node);
    current_node = node;

    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    node = create_noeud(true, "test3", current_node);
    append_a_fils_to_noeud(current_node, node);
    current_node = node;

    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    node = create_noeud(true, "test4", current_node);
    append_a_fils_to_noeud(current_node, node);
    current_node = node;

    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    node = create_noeud(true, "test5", root);
    append_a_fils_to_noeud(root, node);
    current_node = node;

    handle_boolean_test(true, execute_command(c) == 0, __LINE__, __FILE__, info);

    destroy_command(c);

    char **tab_command = malloc(sizeof(char *));
    tab_command[0] = get_alloc_pointer_of_string("test");
    c = create_command(get_alloc_pointer_of_string("pwd"), 1, tab_command);
    handle_boolean_test(true, execute_command(c) == 1, __LINE__, __FILE__, info);
    destroy_command(c);

    tab_command = malloc(sizeof(char *) * 2);
    tab_command[0] = get_alloc_pointer_of_string("test");
    tab_command[1] = get_alloc_pointer_of_string("test");
    c = create_command(get_alloc_pointer_of_string("pwd"), 2, tab_command);
    handle_boolean_test(true, execute_command(c) == 1, __LINE__, __FILE__, info);
    destroy_command(c);

    destroy_noeud(root);

    close_file(out_stream, out_stream_path);

    out_stream = stdin;
    out_stream_path = NULL;
}
