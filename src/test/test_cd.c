#include "test_core.h"

#include "../main/command.h"
#include "../main/constants.h"
#include "../main/file_manager.h"
#include "../main/parser.h"
#include "../main/tree_dir_core.h"
#include <stdio.h>

static void init_folder_struture();

void test_go_to_root(test_info *);
void test_go_to_previous_directory(test_info *);
void test_invalid_invalid_number_args(test_info *);
void test_invalid_path(test_info *);
void test_valid_paths(test_info *);

// TODO: Factorize tests

test_info *test_cd()
{
    // Test setup
    print_test_header("cd");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    init_folder_struture();
    test_invalid_invalid_number_args(info);
    test_invalid_path(info);
    test_go_to_root(info);
    test_go_to_previous_directory(info);
    test_valid_paths(info);

    // End of tests
    destroy_tree();

    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("cd", info);
    return info;
}

static void init_folder_struture()
{
    noeud *root = create_root_noeud();
    current_node = root;

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
}

void test_invalid_invalid_number_args(test_info *info)
{

    print_test_name("Testing cd with an invalid number of args");

    out_stream_path = "src/test/output/test_cd_invalid_number_of_args.txt";
    out_stream = open_file(out_stream_path, "w");

    char *in_stream_path = "src/test/input/test_cd_invalid_number_of_args.txt";

    int output = parse_file(in_stream_path);

    handle_int_test(SUCCESS, output, __LINE__, __FILE__, info);

    command *cmd = create_command("cd", 2, NULL);
    handle_int_test(INVALID_NUMBER_OF_ARGS, cd(cmd), __LINE__, __FILE__, info);
    free(cmd);

    current_node = current_node->racine;

    close_file(out_stream, out_stream_path);
}

void test_invalid_path(test_info *info)
{
    print_test_name("Testing cd with an invalid path");

    out_stream_path = "src/test/output/test_cd_invalid_path.txt";
    out_stream = open_file(out_stream_path, "w");

    char *in_stream_path = "src/test/input/test_cd_invalid_path.txt";

    int output = parse_file(in_stream_path);

    handle_int_test(SUCCESS, output, __LINE__, __FILE__, info);

    char **args = malloc(sizeof(char *));
    args[0] = "/testt";
    command *cmd = create_command("cd", 1, args);
    handle_int_test(INVALID_PATH, cd(cmd), __LINE__, __FILE__, info);
    free(cmd);
    free(args);

    close_file(out_stream, out_stream_path);
}
void test_go_to_root(test_info *info)
{
    print_test_name("Testing cd to root");

    out_stream_path = "src/test/output/test_cd_go_to_root.txt";
    out_stream = open_file(out_stream_path, "w");

    current_node = current_node->racine;
    current_node = get_a_fils_of_noeud(current_node, "test");
    command *cmd = create_command("cd", 0, NULL);
    print(cmd);
    handle_int_test(SUCCESS, cd(cmd), __LINE__, __FILE__, info);
    pwd(cmd);
    free(cmd);

    close_file(out_stream, out_stream_path);
}

void test_go_to_previous_directory(test_info *info)
{

    print_test_name("Testing cd to previous directory");

    out_stream_path = "src/test/output/test_cd_go_to_previous_directory.txt";
    out_stream = open_file(out_stream_path, "w");

    char *in_stream_path =
        "src/test/input/test_cd_go_to_previous_directory.txt";

    int output = parse_file(in_stream_path);

    handle_int_test(SUCCESS, output, __LINE__, __FILE__, info);
    current_node = current_node->racine;
    close_file(out_stream, out_stream_path);
}

void test_valid_paths(test_info *info)
{
    print_test_name("Testing cd with valid paths");

    out_stream_path = "src/test/output/test_cd_valid_paths.txt";
    out_stream = open_file(out_stream_path, "w");

    char *in_stream_path = "src/test/input/test_cd_valid_paths.txt";

    int output = parse_file(in_stream_path);

    handle_int_test(SUCCESS, output, __LINE__, __FILE__, info);

    char **args = malloc(sizeof(char *));
    args[0] = "/test";
    command *cmd = create_command("cd", 1, args);
    handle_int_test(SUCCESS, cd(cmd), __LINE__, __FILE__, info);
    free(cmd);
    free(args);

    current_node = current_node->racine;
    close_file(out_stream, out_stream_path);
}
