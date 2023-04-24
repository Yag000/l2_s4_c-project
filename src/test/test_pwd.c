#include "test_core.h"

#include "../main/command.h"
#include "../main/tree_dir_core.h"

void test_pwd_function(test_info *info);
void test_get_absolute_path_of_node(test_info *info);
void test_get_number_of_node_in_absolute_path(test_info *info);

test_info *test_pwd()
{
    print_test_header("pwd");

    clock_t before = clock();
    // Create the test info
    test_info *info = create_test_info();

    // Add tests here
    test_get_absolute_path_of_node(info);
    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    printf("Test pwd: ");
    print_test_info(info);
    print_test_footer("pwd");
    return info;
}

void test_pwd_function(test_info *info)
{
    // TODO
}

void test_get_absolute_path_of_node(test_info *info)
{
    print_test_name("Test to get the absolute path of node");
    noeud *root = create_root_noeud();

    char *path = get_absolute_path_of_node(root);
    handle_string_test("/", path, __LINE__, __FILE__, info);
    free(path);

    noeud *temp_node_1 = create_noeud(true, "test1", root);
    append_a_fils_to_noeud(root, temp_node_1);
    path = get_absolute_path_of_node(temp_node_1);
    handle_string_test("/test1", path, __LINE__, __FILE__, info);
    free(path);

    noeud *temp_node_2 = create_noeud(true, "test2", root);
    append_a_fils_to_noeud(temp_node_1, temp_node_2);
    path = get_absolute_path_of_node(temp_node_2);
    handle_string_test("/test1/test2", path, __LINE__, __FILE__, info);
    free(path);

    temp_node_1 = create_noeud(false, "test3", root);
    append_a_fils_to_noeud(root, temp_node_1);
    path = get_absolute_path_of_node(temp_node_1);
    handle_string_test("/test3", path, __LINE__, __FILE__, info);
    free(path);

    temp_node_1 = create_noeud(true, "test4", temp_node_2);
    append_a_fils_to_noeud(temp_node_2, temp_node_1);
    path = get_absolute_path_of_node(temp_node_1);
    handle_string_test("/test1/test2/test4", path, __LINE__, __FILE__, info);
    free(path);

    temp_node_2 = create_noeud(true, "test5", temp_node_1);
    append_a_fils_to_noeud(temp_node_1, temp_node_2);
    path = get_absolute_path_of_node(temp_node_2);
    handle_string_test("/test1/test2/test4/test5", path, __LINE__, __FILE__, info);
    free(path);

    destroy_noeud(root);
}
