#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../main/command.h"
#include "../main/constants.h"
#include "../main/file_manager.h"
#include "../main/tree_dir_core.h"
#include "test_core.h"

static void test_mkdir_empty(test_info *);
static void test_mkdir_invalid_name(test_info *);
static void test_mkdir_valid_name(test_info *);
static void test_mkdir_already_exists(test_info *);
static void test_mkdir_long_path(test_info *);

static void invalid_name_format_test_handler(const char *, test_info *);
static node *create_and_test_node_creation_without_path(const char *, test_info *);

static command *string_to_command(const char *);

test_info *test_mkdir()
{
    // Test setup
    print_test_header("mkdir");
    clock_t before = clock();
    test_info *info = create_test_info();

    out_stream_path = "src/resources/unit_tests/output/test_mkdir_invalid_input.txt";
    out_stream = open_file(out_stream_path, "w");

    // Add tests here
    test_mkdir_empty(info);
    test_mkdir_invalid_name(info);
    test_mkdir_valid_name(info);
    test_mkdir_already_exists(info);
    test_mkdir_long_path(info);

    // End of tests
    close_file(out_stream, out_stream_path);
    out_stream = stdout;
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("mkdir", info);
    return info;
}

static void test_mkdir_empty(test_info *info)
{
    print_test_name("Testing mkdir with empty name");

    current_node = create_root_node();

    command *cmd = string_to_command("");
    handle_int_test(INVALID_PATH, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);

    destroy_tree();
}

static void test_mkdir_invalid_name(test_info *info)
{
    print_test_name("Testing mkdir with invalid name");

    current_node = create_root_node();

    invalid_name_format_test_handler("te|st", info);
    invalid_name_format_test_handler("te\\st", info);
    invalid_name_format_test_handler("te*st", info);
    invalid_name_format_test_handler("---", info);
    invalid_name_format_test_handler("hool1-", info);
    invalid_name_format_test_handler("dwe1212hj12b)", info);
    invalid_name_format_test_handler("it_is_a_shame_that_this_does_not_work", info);

    destroy_tree();
}

/*
Executes a mkdir command with the given name.
It will test if the output matches an invalide name format.
*/
static void invalid_name_format_test_handler(const char *name, test_info *info)
{
    command *cmd = string_to_command(name);
    handle_int_test(INVALID_NAME, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);
}

static void test_mkdir_valid_name(test_info *info)
{
    print_test_name("Testing mkdir with valid name");

    current_node = create_root_node();

    create_and_test_node_creation_without_path("test", info);
    current_node = create_and_test_node_creation_without_path("test1", info);

    // Testing the creation of a folder inside a folder, with the same name
    create_and_test_node_creation_without_path("test1", info);

    destroy_tree();
}

static void test_mkdir_already_exists(test_info *info)
{
    print_test_name("Testing mkdir with already existing name");

    current_node = create_root_node();

    node *created_node = create_and_test_node_creation_without_path("test", info);

    char *name = "test";
    command *cmd = string_to_command(name);
    handle_int_test(INVALID_NAME, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);

    // Testing inside a folder different from the root
    current_node = created_node;
    create_and_test_node_creation_without_path("testSon", info);

    name = "testSon";
    cmd = string_to_command(name);
    handle_int_test(INVALID_NAME, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);

    destroy_tree();
}

static void test_mkdir_long_path(test_info *info)
{

    print_test_name("Testing mkdir with long paths");
    current_node = create_root_node();

    current_node = create_and_test_node_creation_without_path("test1", info);
    current_node = create_and_test_node_creation_without_path("test2", info);
    current_node = create_and_test_node_creation_without_path("test3", info);
    current_node = create_and_test_node_creation_without_path("test4", info);

    char *name = "../../test5";
    command *cmd = string_to_command(name);
    handle_int_test(0, mkdir(cmd), __LINE__, __FILE__, info);
    current_node = get_a_fils_of_node(current_node->parent->parent, "test5");
    assert(current_node != NULL);
    handle_boolean_test(true, current_node->is_directory, __LINE__, __FILE__, info);
    destroy_command(cmd);
    char *path = get_absolute_path_of_node(current_node);
    handle_string_test("/test1/test2/test5", path, __LINE__, __FILE__, info);
    free(path);

    current_node = create_and_test_node_creation_without_path("test6", info);
    current_node = create_and_test_node_creation_without_path("test7", info);

    name = "/test";
    cmd = string_to_command(name);
    handle_int_test(0, mkdir(cmd), __LINE__, __FILE__, info);
    current_node = get_a_fils_of_node(current_node->root, "test");
    assert(current_node != NULL);
    handle_boolean_test(true, current_node->is_directory, __LINE__, __FILE__, info);
    handle_string_test("test", current_node->nom, __LINE__, __FILE__, info);
    handle_boolean_test(true, current_node->root == current_node->parent, __LINE__, __FILE__, info);
    destroy_command(cmd);

    destroy_tree();
}

static node *create_and_test_node_creation_without_path(const char *name, test_info *info)
{
    command *cmd = string_to_command(name);
    handle_int_test(0, mkdir(cmd), __LINE__, __FILE__, info);
    node *created_node = get_a_fils_of_node(current_node, name);
    assert(created_node != NULL);
    handle_boolean_test(true, created_node->is_directory, __LINE__, __FILE__, info);
    handle_boolean_test(true, created_node->parent == current_node, __LINE__, __FILE__, info);
    destroy_command(cmd);

    return created_node;
}

static command *string_to_command(const char *name)
{
    char **args = malloc(sizeof(char *));
    args[0] = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(args[0], name);

    char *cmd_name = malloc(sizeof(char) * 6);
    strcpy(cmd_name, "mkdir");

    command *cmd = create_command(cmd_name, 1, args);
    return cmd;
}
