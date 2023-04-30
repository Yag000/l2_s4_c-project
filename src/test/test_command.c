#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "test_core.h"
#include "../main/command.h"
#include "../main/constants.h"
#include "../main/file_manager.h"
#include "../main/tree_dir_core.h"

#define N 10

static void test_write_result_command(test_info *);
static void test_handle_number_of_args(test_info *);
static void test_search_without_create(test_info *info);
static void test_search_with_create(test_info *info);

test_info *test_command()
{
    // Test setup
    print_test_header("command");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    test_write_result_command(info);
    test_handle_number_of_args(info);
    test_search_without_create(info);
    test_search_with_create(info);

    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("command", info);
    return info;
}

static void test_write_result_command(test_info *info)
{
    print_test_name("Testing to write result command in an output");

    out_stream_path = "src/test/output/test_command_write_result_empty.txt";

    out_stream = open_file(out_stream_path, "w");

    if (out_stream != NULL)
    {
        close_file(out_stream, out_stream_path);
    }

    out_stream_path = "src/test/output/test_command_write_result_1.txt";
    out_stream = open_file(out_stream_path, "w");

    if (out_stream != NULL)
    {
        handle_boolean_test(true, write_result_command("test 1212 test") == 0, __LINE__, __FILE__, info);

        close_file(out_stream, out_stream_path);
    }

    out_stream_path = "src/test/output/test_command_write_result_2.txt";
    out_stream = open_file(out_stream_path, "w");

    if (out_stream != NULL)
    {
        handle_boolean_test(true, write_result_command("test 1212 test") == 0, __LINE__, __FILE__, info);
        handle_boolean_test(true, write_result_command("test 1313 test") == 0, __LINE__, __FILE__, info);
        handle_boolean_test(true, write_result_command("test 1414 test") == 0, __LINE__, __FILE__, info);

        close_file(out_stream, out_stream_path);
    }

    out_stream_path = "src/test/output/test_command_write_result_3.txt";
    out_stream = open_file(out_stream_path, "w");

    if (out_stream != NULL)
    {
        char **results = malloc(sizeof(char *) * N);
        assert(results != NULL);

        for (unsigned i = 0; i < N; i++)
        {
            results[i] = out_stream_path;
        }

        handle_boolean_test(true, write_result_lines_command(N, results) == 0, __LINE__, __FILE__, info);

        free(results);

        close_file(out_stream, out_stream_path);
    }

    out_stream = stdout;
}

static void test_handle_number_of_args(test_info *info)
{
    print_test_name("Testing to handle the number of arguments in an output");

    out_stream_path = "src/test/output/test_command_handle_number_of_args.txt";
    out_stream = open_file(out_stream_path, "w");

    if (out_stream != NULL)
    {
        for (int i = 0; i < N + 1; ++i)
        {
            handle_boolean_test(i == (N - i), handle_number_of_args(i, N - i), __LINE__, __FILE__, info);
        }
        close_file(out_stream, out_stream_path);
    }
    out_stream = stdout;
}

static void test_search_without_create(test_info *info)
{
    print_test_name("Testing to search nodes with path without creating new nodes");
    current_node = create_tree_to_test();

    noeud *node = search_node_in_tree(current_node, "test/test2");
    handle_string_test("/test/test2", get_absolute_path_of_node(node), __LINE__, __FILE__, info);

    node = search_node_in_tree(current_node, "test12/../test/../test12/././test13");
    handle_string_test("/test12/test13", get_absolute_path_of_node(node), __LINE__, __FILE__, info);

    node = search_node_in_tree(current_node, "test/.././../test/././");
    handle_string_test("/test", get_absolute_path_of_node(node), __LINE__, __FILE__, info);

    current_node = search_node_in_tree(current_node, "test/test5/test7");
    handle_string_test("/test/test5/test7", get_absolute_path_of_node(current_node), __LINE__, __FILE__, info);

    node = search_node_in_tree(current_node, "../");
    handle_string_test("/test/test5", get_absolute_path_of_node(node), __LINE__, __FILE__, info);

    node = search_node_in_tree(current_node, "../..");
    handle_string_test("/test", get_absolute_path_of_node(node), __LINE__, __FILE__, info);

    node = search_node_in_tree(current_node, "/test12/test15");
    handle_string_test("/test12/test15", get_absolute_path_of_node(node), __LINE__, __FILE__, info);

    node = search_node_in_tree(current_node, "/test/");
    handle_string_test("/test", get_absolute_path_of_node(node), __LINE__, __FILE__, info);

    node = search_node_in_tree(current_node, "/test/test5/.");
    handle_string_test("/test/test5", get_absolute_path_of_node(node), __LINE__, __FILE__, info);

    node = search_node_in_tree(current_node, "test");
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    node = search_node_in_tree(current_node, ".../test5");
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    node = search_node_in_tree(current_node, "/test5");
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    node = search_node_in_tree(current_node, "/test/test12");
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    node = search_node_in_tree(current_node, "../test4/");
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    node = search_node_in_tree(current_node, "/test12/test13/");
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    node = search_node_in_tree(current_node, "/test12/test13/../");
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    destroy_tree();

    current_node = NULL;
}

static void test_search_with_create(test_info *info)
{
    print_test_name("Testing to search nodes with path with creating new nodes");
    current_node = create_tree_to_test();

    noeud *node = search_node_in_tree_with_node_creation(current_node, "test/test2", false);
    handle_string_test("/test/test2", get_absolute_path_of_node(node), __LINE__, __FILE__, info);
    handle_boolean_test(false, are_noeuds_equal(node, search_node_in_tree(current_node, "test/test2")), __LINE__, __FILE__, info);

    destroy_noeud(node);

    node = search_node_in_tree_with_node_creation(current_node, "test12/test42", false);
    handle_string_test("/test12/test42", get_absolute_path_of_node(node), __LINE__, __FILE__, info);
    handle_boolean_test(false, are_noeuds_equal(node, search_node_in_tree(current_node, "test12/test42")), __LINE__, __FILE__, info);
    handle_boolean_test(true, search_node_in_tree(current_node, "test12/test42") == NULL, __LINE__, __FILE__, info);

    destroy_noeud(node);

    node = search_node_in_tree_with_node_creation(current_node, "test/test", true);
    handle_string_test("/test/test", get_absolute_path_of_node(node), __LINE__, __FILE__, info);
    handle_boolean_test(false, are_noeuds_equal(node, search_node_in_tree(current_node, "test")), __LINE__, __FILE__, info);
    handle_boolean_test(true, search_node_in_tree(current_node, "test/test") == NULL, __LINE__, __FILE__, info);

    destroy_noeud(node);

    node = search_node_in_tree_with_node_creation(current_node, "./", false);
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    node = search_node_in_tree_with_node_creation(current_node, "../", false);
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    node = search_node_in_tree_with_node_creation(current_node, ".", false);
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    node = search_node_in_tree_with_node_creation(current_node, "..", false);
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    node = search_node_in_tree_with_node_creation(current_node, "./.././..", false);
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    node = search_node_in_tree_with_node_creation(current_node, "./.././../test/.", false);
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    node = search_node_in_tree_with_node_creation(current_node, "./.././../test/./abc_efg", false);
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    node = search_node_in_tree_with_node_creation(current_node, "./.././../test/", false);
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    node = search_node_in_tree_with_node_creation(current_node, "test/test/", false);
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    node = search_node_in_tree_with_node_creation(current_node, "./.././../test/new/test", false);
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    destroy_tree();

    current_node = NULL;
}