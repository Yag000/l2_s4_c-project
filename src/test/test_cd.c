#include "test_core.h"

#include "../main/command.h"
#include "../main/constants.h"
#include "../main/file_manager.h"
#include "../main/parser.h"
#include "../main/tree_dir_core.h"

static void init_folder_struture();

static void test_error_codes(test_info *);
static void test_go_to_root(test_info *);
static void test_go_to_previous_directory(test_info *);
static void test_invalid_invalid_number_args(test_info *);
static void test_invalid_path(test_info *);
static void test_valid_paths(test_info *);

static void execute_test(test_info *, char *, char *);

test_info *test_cd()
{
    // Test setup
    print_test_header("cd");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    init_folder_struture();
    test_error_codes(info);
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

static void test_error_codes(test_info *info)
{

    print_test_name("Testing return values of cd");

    out_stream_path = "src/test/output/test_cd_return_values.txt";
    out_stream = open_file(out_stream_path, "w");

    // Invalid number of arguments
    command *cmd = create_command("cd", 2, NULL);
    handle_int_test(INVALID_NUMBER_OF_ARGS, cd(cmd), __LINE__, __FILE__, info);
    free(cmd);

    // Invalid path
    char **args = malloc(sizeof(char *));
    args[0] = "/testt";
    cmd = create_command("cd", 1, args);
    handle_int_test(INVALID_PATH, cd(cmd), __LINE__, __FILE__, info);
    free(cmd);
    free(args);

    // Valid input
    args = malloc(sizeof(char *));
    args[0] = "/test";
    cmd = create_command("cd", 1, args);
    handle_int_test(SUCCESS, cd(cmd), __LINE__, __FILE__, info);
    free(cmd);
    free(args);

    current_node = current_node->racine;
    close_file(out_stream, out_stream_path);
}

static void test_invalid_invalid_number_args(test_info *info)
{
    print_test_name("Testing cd with an invalid number of args");
    execute_test(info, "src/test/input/test_cd_invalid_number_of_args.txt",
                 "src/test/output/test_cd_invalid_number_of_args.txt");
}

static void test_invalid_path(test_info *info)
{
    print_test_name("Testing cd with an invalid path");
    execute_test(info, "src/test/input/test_cd_invalid_path.txt", "src/test/output/test_cd_invalid_path.txt");
}

static void test_go_to_root(test_info *info)
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

static void test_go_to_previous_directory(test_info *info)
{
    print_test_name("Testing cd to previous directory");
    execute_test(info, "src/test/input/test_cd_go_to_previous_directory.txt",
                 "src/test/output/test_cd_go_to_previous_directory.txt");
}

static void test_valid_paths(test_info *info)
{
    print_test_name("Testing cd with valid paths");
    execute_test(info, "src/test/input/test_cd_valid_paths.txt", "src/test/output/test_valid_paths.txt");
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
