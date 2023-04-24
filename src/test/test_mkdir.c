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

static command *string_to_command(char *name);

test_info *test_mkdir()
{
    print_test_header("mkdir");

    clock_t before = clock();
    // Create the test info
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

    command *cmd = string_to_command("");

    handle_int_test(INVALID_NAME, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);

    destroy_root();
}

static void test_mkdir_invalid_name(test_info *info)
{
    print_test_name("Testing mkdir with invalid name");

    current_node = create_root_noeud();

    command *cmd = string_to_command("te/st");
    handle_int_test(INVALID_NAME, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);

    cmd = string_to_command("te\\st");
    handle_int_test(INVALID_NAME, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);

    cmd = string_to_command("te*st");
    handle_int_test(INVALID_NAME, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);

    cmd = string_to_command("---");
    handle_int_test(INVALID_NAME, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);

    cmd = string_to_command("hool1-");
    handle_int_test(INVALID_NAME, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);

    cmd = string_to_command("dwe1212hj12b)");
    handle_int_test(INVALID_NAME, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);

    cmd = string_to_command("it_is_a_shame_that_this_does_not_work");
    handle_int_test(INVALID_NAME, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);

    destroy_root();
}

static void test_mkdir_valid_name(test_info *info)
{
    print_test_name("Testing mkdir with valid name");

    current_node = create_root_noeud();

    char *name = "test";
    command *cmd = string_to_command(name);
    handle_int_test(0, mkdir(cmd), __LINE__, __FILE__, info);
    noeud *created_node = get_a_fils_of_noeud(current_node, name);
    assert(created_node != NULL);
    handle_boolean_test(true, created_node->est_dossier, __LINE__, __FILE__, info);
    handle_boolean_test(true, created_node->pere == current_node, __LINE__, __FILE__, info);
    destroy_command(cmd);

    name = "test1";
    cmd = string_to_command(name);
    handle_int_test(0, mkdir(cmd), __LINE__, __FILE__, info);
    created_node = get_a_fils_of_noeud(current_node, name);
    assert(created_node != NULL);
    handle_boolean_test(true, created_node->est_dossier, __LINE__, __FILE__, info);
    handle_boolean_test(true, created_node->pere == current_node, __LINE__, __FILE__, info);
    destroy_command(cmd);

    // Testing the creation of a folder inside a folder, with the same name
    current_node = created_node;
    name = "test1";
    cmd = string_to_command(name);
    handle_int_test(0, mkdir(cmd), __LINE__, __FILE__, info);
    created_node = get_a_fils_of_noeud(current_node, name);
    assert(created_node != NULL);
    handle_boolean_test(true, created_node->est_dossier, __LINE__, __FILE__, info);
    handle_boolean_test(true, created_node->pere == current_node, __LINE__, __FILE__, info);
    destroy_command(cmd);

    destroy_root();
}

static void test_mkdir_already_exists(test_info *info)
{
    print_test_name("Testing mkdir with already existing name");

    current_node = create_root_noeud();

    char *name = "test";
    command *cmd = string_to_command(name);
    handle_int_test(0, mkdir(cmd), __LINE__, __FILE__, info);
    noeud *created_node = get_a_fils_of_noeud(current_node, name);
    assert(created_node != NULL);
    destroy_command(cmd);

    name = "test";
    cmd = string_to_command(name);
    handle_int_test(FATAL_ERROR, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);

    // Testing inside a folder different from the root
    current_node = created_node;
    name = "testSon";
    cmd = string_to_command(name);
    handle_int_test(0, mkdir(cmd), __LINE__, __FILE__, info);
    created_node = get_a_fils_of_noeud(current_node, name);
    assert(created_node != NULL);
    destroy_command(cmd);

    name = "testSon";
    cmd = string_to_command(name);
    handle_int_test(FATAL_ERROR, mkdir(cmd), __LINE__, __FILE__, info);
    destroy_command(cmd);

    destroy_root();
}
static command *string_to_command(char *name)
{
    char **args = malloc(sizeof(char *));
    args[0] = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(args[0], name);

    char *cmd_name = malloc(sizeof(char) * 6);
    strcpy(cmd_name, "mkdir");

    command *cmd = create_command(cmd_name, 1, args);
    return cmd;
}
