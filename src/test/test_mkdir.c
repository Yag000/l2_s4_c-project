#include <assert.h>
#include <string.h>

#include "test_core.h"
#include "../main/constants.h"
#include "../main/command.h"
#include "../main/tree_dir_core.h"

static void test_mkdir_empty(test_info *info);
static void test_mkdir_invalid_name(test_info *info);
static void test_mkdir_valid_name(test_info *info);
static void test_mkdir_already_exists(test_info *info);

static void invalid_name_format_test_handler(const char *name, test_info *info);
static noeud *create_and_test_node_creation(const char *name, test_info *info);

static command *string_to_command(const char *name);

// TODO: add more tests when ls and cd are implemented

test_info *test_mkdir()
{
    // Create the test info
    print_test_header("mkdir");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    test_mkdir_empty(info);
    test_mkdir_invalid_name(info);
    test_mkdir_valid_name(info);
    test_mkdir_already_exists(info);

    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    printf("Test mkdir: ");
    print_test_info(info);
    print_test_footer("mkdir");
    return info;
}

static void test_mkdir_empty(test_info *info)
{
    print_test_name("Testing mkdir with empty name");

    current_node = create_root_noeud();
    invalid_name_format_test_handler("", info);
    destroy_root();
}

static void test_mkdir_invalid_name(test_info *info)
{
    print_test_name("Testing mkdir with invalid name");

    current_node = create_root_noeud();

    invalid_name_format_test_handler("te/st", info);
    invalid_name_format_test_handler("te\\st", info);
    invalid_name_format_test_handler("te*st", info);
    invalid_name_format_test_handler("---", info);
    invalid_name_format_test_handler("hool1-", info);
    invalid_name_format_test_handler("dwe1212hj12b)", info);
    invalid_name_format_test_handler("it_is_a_shame_that_this_does_not_work", info);

    destroy_root();
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

    current_node = create_root_noeud();

    noeud *created_node = create_and_test_node_creation("test", info);
    created_node = create_and_test_node_creation("test1", info);

    // Testing the creation of a folder inside a folder, with the same name
    current_node = created_node;
    created_node = create_and_test_node_creation("test1", info);

    destroy_root();
}

static void test_mkdir_already_exists(test_info *info)
{
    print_test_name("Testing mkdir with already existing name");

    current_node = create_root_noeud();

    noeud *created_node = create_and_test_node_creation("test", info);

    char *name = "test";
    command *cmd = string_to_command(name);
    handle_int_test(FATAL_ERROR, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);

    // Testing inside a folder different from the root
    current_node = created_node;
    created_node = create_and_test_node_creation("testSon", info);

    name = "testSon";
    cmd = string_to_command(name);
    handle_int_test(FATAL_ERROR, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);

    destroy_root();
}

static noeud *create_and_test_node_creation(const char *name, test_info *info)
{
    command *cmd = string_to_command(name);
    handle_int_test(0, mkdir(cmd), __LINE__, __FILE__, info);
    noeud *created_node = get_a_fils_of_noeud(current_node, name);
    assert(created_node != NULL);
    handle_boolean_test(true, created_node->est_dossier, __LINE__, __FILE__, info);
    handle_boolean_test(true, created_node->pere == current_node, __LINE__, __FILE__, info);
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
