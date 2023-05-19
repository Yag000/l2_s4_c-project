#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../main/command.h"
#include "../main/constants.h"
#include "../main/file_manager.h"
#include "../main/string_utils.h"
#include "../main/tree_dir_core.h"
#include "test_core.h"

static void test_pwd_function(test_info *);

test_info *test_pwd()
{
    // Test setup
    print_test_header("pwd");
    clock_t before = clock();
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

    out_stream_path = "src/resources/unit_tests/output/test_pwd.txt";
    out_stream = open_file(out_stream_path, "w");

    char **tab_command = malloc(0);
    assert(tab_command != NULL);
    command *c = create_command(get_alloc_pointer_of_string("pwd"), 0, tab_command);

    noeud *root = create_root_noeud();
    current_node = root;

    handle_boolean_test(true, execute_command(c) == SUCCESS, __LINE__, __FILE__, info);

    noeud *node = create_noeud(true, "test", root);
    append_a_fils_to_noeud(root, node);
    current_node = node;

    handle_boolean_test(true, execute_command(c) == SUCCESS, __LINE__, __FILE__, info);

    node = create_noeud(true, "test2", current_node);
    append_a_fils_to_noeud(current_node, node);
    current_node = node;

    handle_boolean_test(true, execute_command(c) == SUCCESS, __LINE__, __FILE__, info);

    node = create_noeud(true, "test3", current_node);
    append_a_fils_to_noeud(current_node, node);
    current_node = node;

    handle_boolean_test(true, execute_command(c) == SUCCESS, __LINE__, __FILE__, info);

    node = create_noeud(true, "test4", current_node);
    append_a_fils_to_noeud(current_node, node);
    current_node = node;

    handle_boolean_test(true, execute_command(c) == SUCCESS, __LINE__, __FILE__, info);

    node = create_noeud(true, "test5", root);
    append_a_fils_to_noeud(root, node);
    current_node = node;

    handle_boolean_test(true, execute_command(c) == SUCCESS, __LINE__, __FILE__, info);

    destroy_command(c);

    tab_command = malloc(sizeof(char *));
    assert(tab_command != NULL);
    tab_command[0] = get_alloc_pointer_of_string("test");
    c = create_command(get_alloc_pointer_of_string("pwd"), 1, tab_command);
    handle_boolean_test(true, execute_command(c) == INVALID_NUMBER_OF_ARGS, __LINE__, __FILE__, info);
    destroy_command(c);

    tab_command = malloc(sizeof(char *) * 2);
    assert(tab_command != NULL);
    tab_command[0] = get_alloc_pointer_of_string("test");
    tab_command[1] = get_alloc_pointer_of_string("test");
    c = create_command(get_alloc_pointer_of_string("pwd"), 2, tab_command);
    handle_boolean_test(true, execute_command(c) == INVALID_NUMBER_OF_ARGS, __LINE__, __FILE__, info);
    destroy_command(c);

    destroy_noeud(root);

    close_file(out_stream, out_stream_path);

    out_stream = stdout;
    out_stream_path = NULL;

    current_node = NULL;
}
