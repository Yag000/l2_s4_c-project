#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../main/command.h"
#include "../main/constants.h"
#include "../main/file_manager.h"
#include "../main/parser.h"
#include "../main/tree_dir_core.h"
#include "test_core.h"

static void test_touch_empty(test_info *);
static void test_touch_invalid_name(test_info *);
static void test_touch_valid_name(test_info *);
static void test_touch_already_exists(test_info *);
static void test_touch_long_path(test_info *);

static void invalid_name_format_test_handler(char *, test_info *);
static void execute_test(test_info *, char *, char *);

test_info *test_touch()
{
    // Test setup
    print_test_header("touch");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    test_touch_empty(info);
    test_touch_invalid_name(info);
    test_touch_valid_name(info);
    test_touch_already_exists(info);
    test_touch_long_path(info);

    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("touch", info);
    return info;
}

static void test_touch_empty(test_info *info)
{
    print_test_name("Testing touch with empty name");
    out_stream_path = "src/resources/unit_tests/output/test_touch_empty.txt";
    out_stream = open_file(out_stream_path, "w");

    current_node = create_root_noeud();

    char **args = malloc(sizeof(char *));
    args[0] = "";

    command *cmd = create_command("touch", 1, args);
    handle_int_test(INVALID_PATH, touch(cmd), __LINE__, __FILE__, info);

    free(args);
    free(cmd);

    destroy_tree();

    close_file(out_stream, out_stream_path);
}

static void test_touch_invalid_name(test_info *info)
{
    print_test_name("Testing touch with invalid name");
    out_stream_path = "src/resources/unit_tests/output/test_touch_invalid_name.txt";
    out_stream = open_file(out_stream_path, "w");

    current_node = create_root_noeud();

    invalid_name_format_test_handler("te|st", info);
    invalid_name_format_test_handler("te\\st", info);
    invalid_name_format_test_handler("te*st", info);
    invalid_name_format_test_handler("---", info);
    invalid_name_format_test_handler("hool1-", info);
    invalid_name_format_test_handler("dwe1212hj12b)", info);
    invalid_name_format_test_handler("it_is_a_shame_that_this_does_not_work", info);

    destroy_tree();

    close_file(out_stream, out_stream_path);
}

/*
Executes a touch command with the given name.
It will test if the output matches an invalid name format.
*/
static void invalid_name_format_test_handler(char *name, test_info *info)
{
    char **args = malloc(sizeof(char *));
    args[0] = name;

    command *cmd = create_command("touch", 1, args);
    handle_int_test(INVALID_NAME, touch(cmd), __LINE__, __FILE__, info);

    free(args);
    free(cmd);
}

static void test_touch_valid_name(test_info *info)
{
    print_test_name("Testing touch with valid name");

    current_node = create_root_noeud();
    execute_test(info, "src/resources/unit_tests/input/test_touch_valid_path.txt",
                 "src/resources/unit_tests/output/test_touch_valid_path.txt");
    destroy_tree();
}

static void test_touch_already_exists(test_info *info)
{
    print_test_name("Testing touch with already existing name");

    current_node = create_root_noeud();
    execute_test(info, "src/resources/unit_tests/input/test_touch_already_exists.txt",
                 "src/resources/unit_tests/output/test_touch_already_exists.txt");
    destroy_tree();
}

static void test_touch_long_path(test_info *info)
{
    print_test_name("Testing touch with long paths");
    current_node = create_root_noeud();

    execute_test(info, "src/resources/unit_tests/input/test_touch_long_path.txt",
                 "src/resources/unit_tests/output/test_touch_long_path.txt");

    destroy_tree();
}

static void execute_test(test_info *info, char *input, char *output)
{
    out_stream_path = output;
    out_stream = open_file(out_stream_path, "w");

    int result = parse_file(input);

    handle_int_test(SUCCESS, result, __LINE__, __FILE__, info);

    current_node = current_node->racine;
    close_file(out_stream, out_stream_path);
}
