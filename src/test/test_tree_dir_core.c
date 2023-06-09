#include <stdio.h>
#include <stdlib.h>

#include "../main/constants.h"
#include "../main/tree_dir_core.h"
#include "test_core.h"

static void test_create_node(test_info *);
static void test_is_valid_name_of_node(test_info *);
static void test_are_node_equal(test_info *);
static void test_is_root_node(test_info *);
static void test_is_children_of_node_empty(test_info *);
static void test_create_list_node(test_info *);
static void test_contains(test_info *);
static void test_get(test_info *);
static void test_append(test_info *);
static void test_remove(test_info *);
static void test_get_absolute_path_of_node(test_info *);
static void test_search_without_create(test_info *);
static void test_search_with_create(test_info *);

test_info *test_tree_dir_core()
{
    // Test setup
    print_test_header("tree dir core");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    test_create_node(info);
    test_is_valid_name_of_node(info);
    test_are_node_equal(info);
    test_is_root_node(info);
    test_is_children_of_node_empty(info);
    test_create_list_node(info);
    test_contains(info);
    test_get(info);
    test_append(info);
    test_remove(info);
    test_get_absolute_path_of_node(info);
    test_search_without_create(info);
    test_search_with_create(info);

    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("tree dir core", info);
    return info;
}

static void test_create_node(test_info *info)
{
    print_test_name("Testing to create a node");

    node *parent = create_root_node();
    handle_boolean_test(true, are_nodes_equal(parent, parent->parent), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_nodes_equal(parent, parent->root), __LINE__, __FILE__, info);
    handle_boolean_test(true, parent->is_directory, __LINE__, __FILE__, info);

    node *node1 = create_node(false, "test", parent);

    handle_boolean_test(false, node1->is_directory, __LINE__, __FILE__, info);
    handle_string_test("test", node1->name, __LINE__, __FILE__, info);
    handle_boolean_test(true, are_nodes_equal(parent, node1->parent), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_nodes_equal(parent->root, node1->root), __LINE__, __FILE__, info);
    handle_boolean_test(true, node1->children == NULL, __LINE__, __FILE__, info);

    list_node *node_list = create_list_node(node1);
    node *node2 = create_node_with_children(true, "test2", parent, node_list);

    handle_boolean_test(true, node2->is_directory, __LINE__, __FILE__, info);
    handle_string_test("test2", node2->name, __LINE__, __FILE__, info);
    handle_boolean_test(true, are_nodes_equal(parent, node2->parent), __LINE__, __FILE__, info);
    handle_boolean_test(true, node2->children != NULL, __LINE__, __FILE__, info);

    if (node2->children != NULL)
    {
        handle_boolean_test(true, are_nodes_equal(node2->children->no, node1), __LINE__, __FILE__, info);
    }

    destroy_node(node2);
    destroy_node(parent);
}

static void test_is_valid_name_of_node(test_info *info)
{
    print_test_name("Testing to handle valid and invalid names of node");

    handle_boolean_test(false, is_valid_name_node(""), __LINE__, __FILE__, info);
    handle_boolean_test(false, is_valid_name_node("."), __LINE__, __FILE__, info);
    handle_boolean_test(false, is_valid_name_node(".."), __LINE__, __FILE__, info);

    handle_boolean_test(false, is_valid_name_node("/"), __LINE__, __FILE__, info);
    handle_boolean_test(false, is_valid_name_node("/abcd"), __LINE__, __FILE__, info);
    handle_boolean_test(false, is_valid_name_node("abcd/"), __LINE__, __FILE__, info);
    handle_boolean_test(false, is_valid_name_node("abcd/efcg"), __LINE__, __FILE__, info);

    handle_boolean_test(true, is_valid_name_node("na2me1"), __LINE__, __FILE__, info);
    handle_boolean_test(true, is_valid_name_node("21na2me1"), __LINE__, __FILE__, info);
    handle_boolean_test(true, is_valid_name_node("12345678900987654321"), __LINE__, __FILE__, info);
}

static void test_are_node_equal(test_info *info)
{
    print_test_name("Testing if two nodes are equal");

    node *root_node1 = create_root_node();
    node *root_node2 = create_root_node();

    handle_boolean_test(true, are_nodes_equal(NULL, NULL), __LINE__, __FILE__, info);
    handle_boolean_test(false, are_nodes_equal(root_node1, NULL), __LINE__, __FILE__, info);
    handle_boolean_test(false, are_nodes_equal(root_node1, root_node2), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_nodes_equal(root_node1, root_node1), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_nodes_equal(root_node2, root_node2), __LINE__, __FILE__, info);

    node *node1 = create_node(false, "test", root_node1);
    append_child_to_node(root_node1, node1);
    handle_boolean_test(true, are_nodes_equal(node1, node1), __LINE__, __FILE__, info);

    node *node2 = create_node(false, "test", root_node2);
    append_child_to_node(root_node2, node2);
    handle_boolean_test(true, are_nodes_equal(node2, node2), __LINE__, __FILE__, info);
    handle_boolean_test(false, are_nodes_equal(node1, node2), __LINE__, __FILE__, info);

    destroy_node(root_node1);
    destroy_node(root_node2);
}

static void test_is_root_node(test_info *info)
{
    print_test_name("Testing if a node is a root node");

    node *root_node = create_root_node();
    handle_boolean_test(true, is_root_node(root_node), __LINE__, __FILE__, info);

    node *node1 = create_node(true, "test", root_node);
    append_child_to_node(root_node, node1);
    handle_boolean_test(false, is_root_node(node1), __LINE__, __FILE__, info);

    node1->parent = node1;
    node1->root = node1;
    handle_boolean_test(false, is_root_node(node1), __LINE__, __FILE__, info);

    destroy_node(root_node);
}

static void test_is_children_of_node_empty(test_info *info)
{
    print_test_name("Testing if children of node is empty");

    node *root = create_root_node();

    handle_boolean_test(true, is_children_of_node_empty(root), __LINE__, __FILE__, info);
    node *node1 = create_node(false, "test", root);

    append_child_to_node(root, node1);
    handle_boolean_test(false, is_children_of_node_empty(root), __LINE__, __FILE__, info);

    destroy_node(root);
}

static void test_create_list_node(test_info *info)
{
    print_test_name("Testing to create a list node");

    node *root_node = create_root_node();

    node *node1 = create_node(false, "test1", root_node);

    root_node->children = create_list_node(node1);
    handle_string_test("test1", root_node->children->no->name, __LINE__, __FILE__, info);
    handle_boolean_test(true, root_node->children->succ == NULL, __LINE__, __FILE__, info);

    node *node2 = create_node(false, "test2", root_node);

    handle_boolean_test(true, append_list_node(root_node->children, node2) == SUCCESS, __LINE__, __FILE__, info);
    handle_boolean_test(true, root_node->children->succ != NULL, __LINE__, __FILE__, info);
    handle_boolean_test(true, root_node->children->succ->succ == NULL, __LINE__, __FILE__, info);
    handle_string_test("test2", root_node->children->succ->no->name, __LINE__, __FILE__, info);

    destroy_node(root_node);
}

static void test_contains(test_info *info)
{
    print_test_name("Testing contains list node");

    node *root_node = create_root_node();

    node *node1 = create_node(true, "test", root_node);
    handle_boolean_test(false, contains_list_node(root_node->children, node1), __LINE__, __FILE__, info);
    append_child_to_node(root_node, node1);
    handle_boolean_test(true, contains_list_node(root_node->children, node1), __LINE__, __FILE__, info);

    append_child_to_node(root_node, create_node(false, "test2", root_node));
    append_child_to_node(root_node, create_node(false, "test3", root_node));
    node1 = create_node(false, "test4", root_node);
    handle_boolean_test(false, contains_list_node(root_node->children, node1), __LINE__, __FILE__, info);

    append_child_to_node(root_node, node1);
    handle_boolean_test(true, contains_list_node(root_node->children, node1), __LINE__, __FILE__, info);
    append_child_to_node(root_node, create_node(false, "test5", root_node));
    handle_boolean_test(true, contains_list_node(root_node->children, node1), __LINE__, __FILE__, info);

    destroy_node(root_node);
}

static void test_get(test_info *info)
{

    print_test_name("Testing to get a node in a list_node with name");

    node *root_node = create_root_node();

    node *node1 = create_node(false, "test", root_node);
    append_child_to_node(root_node, node1);
    handle_boolean_test(true, are_nodes_equal(get_a_child_of_node(root_node, "test"), node1), __LINE__, __FILE__, info);

    remove_a_child_from_children(root_node, node1);
    handle_boolean_test(true, get_a_child_of_node(root_node, "test") == NULL, __LINE__, __FILE__, info);

    destroy_node(node1);

    node1 = create_node(false, "test3", root_node);
    append_child_to_node(root_node, create_node(false, "test1", root_node));
    append_child_to_node(root_node, create_node(false, "test2", root_node));
    append_child_to_node(root_node, node1);
    append_child_to_node(root_node, create_node(false, "test4", root_node));
    handle_boolean_test(true, are_nodes_equal(get_a_child_of_node(root_node, "test3"), node1), __LINE__, __FILE__,
                        info);

    remove_a_child_from_children(root_node, node1);
    handle_boolean_test(true, get_a_child_of_node(root_node, "test3") == NULL, __LINE__, __FILE__, info);

    destroy_node(node1);
    destroy_node(root_node);
}

static void test_append(test_info *info)
{

    print_test_name("Testing to append a node in a list_node");

    node *root_node = create_root_node();
    handle_boolean_test(true, root_node->children == NULL, __LINE__, __FILE__, info);

    node *node1 = create_node(false, "test", root_node);
    handle_boolean_test(true, append_child_to_node(root_node, node1) == SUCCESS, __LINE__, __FILE__, info);
    handle_boolean_test(true, root_node->children != NULL, __LINE__, __FILE__, info);
    handle_boolean_test(true, are_nodes_equal(root_node->children->no, node1), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_nodes_equal(root_node->children->no->parent, root_node), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_nodes_equal(root_node->children->no->root, root_node), __LINE__, __FILE__, info);

    node *node2 = create_node(false, "test2", root_node);
    handle_boolean_test(false, contains_list_node(root_node->children, node2), __LINE__, __FILE__, info);
    handle_boolean_test(true, append_child_to_node(root_node, node2) == SUCCESS, __LINE__, __FILE__, info);
    handle_boolean_test(true, contains_list_node(root_node->children, node2), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_nodes_equal(node2->parent, root_node), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_nodes_equal(node2->root, root_node), __LINE__, __FILE__, info);

    handle_boolean_test(true, append_child_to_node(node1, node2) == INVALID_SELECTION, __LINE__, __FILE__, info);
    handle_boolean_test(true, append_child_to_node(node2, node1) == INVALID_SELECTION, __LINE__, __FILE__, info);

    handle_boolean_test(true, append_child_to_node(root_node, node2) == INVALID_NAME, __LINE__, __FILE__, info);

    handle_boolean_test(true, append_child_to_node(root_node, create_node(false, "test3", root_node)) == SUCCESS,
                        __LINE__, __FILE__, info);
    handle_boolean_test(true, contains_list_node(root_node->children, node2), __LINE__, __FILE__, info);

    handle_boolean_test(true, size_list_node(root_node->children) == 3, __LINE__, __FILE__, info);

    node1 = create_node(true, "test", root_node);
    handle_boolean_test(true, append_child_to_node(root_node, node1) == INVALID_NAME, __LINE__, __FILE__, info);
    free(node1);

    node1 = create_node(false, "test", root_node);
    handle_boolean_test(true, append_child_to_node(root_node, node1) == INVALID_NAME, __LINE__, __FILE__, info);
    free(node1);

    node1 = create_node(true, "test2", root_node);
    handle_boolean_test(true, append_child_to_node(root_node, node1) == INVALID_NAME, __LINE__, __FILE__, info);
    free(node1);

    node1 = create_node(true, "test3", root_node);
    handle_boolean_test(true, append_child_to_node(root_node, node1) == INVALID_NAME, __LINE__, __FILE__, info);
    free(node1);
    destroy_node(root_node);
}

static void test_remove(test_info *info)
{
    print_test_name("Testing to remove a node in a list_node");

    node *root_node = create_root_node();

    node *node1 = create_node(false, "test", root_node);
    append_child_to_node(root_node, node1);
    handle_boolean_test(true, are_nodes_equal(root_node->children->no, node1), __LINE__, __FILE__, info);

    handle_boolean_test(true, remove_a_child_from_children(root_node, node1) == SUCCESS, __LINE__, __FILE__, info);
    handle_boolean_test(true, root_node->children == NULL, __LINE__, __FILE__, info);
    handle_boolean_test(false, remove_a_child_from_children(root_node, node1) == SUCCESS, __LINE__, __FILE__, info);

    destroy_node(node1);

    append_child_to_node(root_node, create_node(false, "test1", root_node));
    append_child_to_node(root_node, create_node(false, "test2", root_node));
    node1 = create_node(false, "test3", root_node);
    append_child_to_node(root_node, node1);
    append_child_to_node(root_node, create_node(false, "test4", root_node));

    handle_boolean_test(true, contains_node(root_node, node1), __LINE__, __FILE__, info);
    handle_boolean_test(true, remove_a_child_from_children(root_node, node1) == SUCCESS, __LINE__, __FILE__, info);
    handle_boolean_test(false, contains_node(root_node, node1), __LINE__, __FILE__, info);
    handle_boolean_test(true, remove_a_child_from_children(root_node, node1) == INVALID_SELECTION, __LINE__, __FILE__,
                        info);

    destroy_node(node1);
    destroy_node(root_node);

    root_node = create_root_node();
    node1 = create_node(false, "test", root_node);
    append_child_to_node(root_node, node1);

    handle_boolean_test(true, remove_a_child_of_node(root_node, node1->name) == SUCCESS, __LINE__, __FILE__, info);
    handle_boolean_test(true, root_node->children == NULL, __LINE__, __FILE__, info);
    handle_boolean_test(true, remove_a_child_of_node(root_node, node1->name) == INVALID_SELECTION, __LINE__, __FILE__,
                        info);

    destroy_node(root_node);

    node1 = create_root_node();
    list_node *list = create_list_node(node1);
    handle_boolean_test(true, remove_list_node(list, node1) == NULL, __LINE__, __FILE__, info);

    destroy_node(node1);
}

static void test_get_absolute_path_of_node(test_info *info)
{
    print_test_name("Test to get the absolute path of node");
    node *root = create_root_node();

    char *path = get_absolute_path_of_node(root);
    handle_string_test("/", path, __LINE__, __FILE__, info);
    free(path);

    node *temp_node_1 = create_node(true, "test1", root);
    append_child_to_node(root, temp_node_1);
    path = get_absolute_path_of_node(temp_node_1);
    handle_string_test("/test1", path, __LINE__, __FILE__, info);
    free(path);

    node *temp_node_2 = create_node(true, "test2", root);
    append_child_to_node(temp_node_1, temp_node_2);
    path = get_absolute_path_of_node(temp_node_2);
    handle_string_test("/test1/test2", path, __LINE__, __FILE__, info);
    free(path);

    temp_node_1 = create_node(false, "test3", root);
    append_child_to_node(root, temp_node_1);
    path = get_absolute_path_of_node(temp_node_1);
    handle_string_test("/test3", path, __LINE__, __FILE__, info);
    free(path);

    temp_node_1 = create_node(true, "test4", temp_node_2);
    append_child_to_node(temp_node_2, temp_node_1);
    path = get_absolute_path_of_node(temp_node_1);
    handle_string_test("/test1/test2/test4", path, __LINE__, __FILE__, info);
    free(path);

    temp_node_2 = create_node(true, "test5", temp_node_1);
    append_child_to_node(temp_node_1, temp_node_2);
    path = get_absolute_path_of_node(temp_node_2);
    handle_string_test("/test1/test2/test4/test5", path, __LINE__, __FILE__, info);
    free(path);

    destroy_node(root);
}

static void test_search_without_create(test_info *info)
{
    print_test_name("Testing to search nodes with path without creating new nodes");
    current_node = create_basic_testing_tree();
    char *absolute_path;

    node *node1 = search_node_in_tree(current_node, "test/test2");
    absolute_path = get_absolute_path_of_node(node1);
    handle_string_test("/test/test2", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node1 = search_node_in_tree(current_node, "test12/../test/../test12/././test13");
    absolute_path = get_absolute_path_of_node(node1);
    handle_string_test("/test12/test13", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node1 = search_node_in_tree(current_node, "test/.././../test/./.");
    absolute_path = get_absolute_path_of_node(node1);
    handle_string_test("/test", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    current_node = search_node_in_tree(current_node, "test/test5/test7");
    absolute_path = get_absolute_path_of_node(current_node);
    handle_string_test("/test/test5/test7", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node1 = search_node_in_tree(current_node, "..");
    absolute_path = get_absolute_path_of_node(node1);
    handle_string_test("/test/test5", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node1 = search_node_in_tree(current_node, "../..");
    absolute_path = get_absolute_path_of_node(node1);
    handle_string_test("/test", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node1 = search_node_in_tree(current_node, "/test12/test15");
    absolute_path = get_absolute_path_of_node(node1);
    handle_string_test("/test12/test15", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node1 = search_node_in_tree(current_node, "/test");
    absolute_path = get_absolute_path_of_node(node1);
    handle_string_test("/test", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node1 = search_node_in_tree(current_node, "/test/test5/.");
    absolute_path = get_absolute_path_of_node(node1);
    handle_string_test("/test/test5", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node1 = search_node_in_tree(current_node, "");
    handle_boolean_test(true, node1 == NULL, __LINE__, __FILE__, info);

    node1 = search_node_in_tree(current_node, "test");
    handle_boolean_test(true, node1 == NULL, __LINE__, __FILE__, info);

    node1 = search_node_in_tree(current_node, ".../test5");
    handle_boolean_test(true, node1 == NULL, __LINE__, __FILE__, info);

    node1 = search_node_in_tree(current_node, "/test5");
    handle_boolean_test(true, node1 == NULL, __LINE__, __FILE__, info);

    node1 = search_node_in_tree(current_node, "/test/test12");
    handle_boolean_test(true, node1 == NULL, __LINE__, __FILE__, info);

    node1 = search_node_in_tree(current_node, "../test4/");
    handle_boolean_test(true, node1 == NULL, __LINE__, __FILE__, info);

    node1 = search_node_in_tree(current_node, "/test12/test13/");
    handle_boolean_test(true, node1 == NULL, __LINE__, __FILE__, info);

    node1 = search_node_in_tree(current_node, "/test12/test13/..");
    handle_boolean_test(true, node1 == NULL, __LINE__, __FILE__, info);

    destroy_tree();

    current_node = NULL;
}

static void test_search_with_create(test_info *info)
{
    print_test_name("Testing to search nodes with path with creating new nodes");
    current_node = create_basic_testing_tree();
    char *absolute_path;

    node *node1 = search_node_in_tree_with_node_creation(current_node, "test/test2", false);
    absolute_path = get_absolute_path_of_node(node1);
    handle_string_test("/test/test2", absolute_path, __LINE__, __FILE__, info);
    handle_boolean_test(false, are_nodes_equal(node1, search_node_in_tree(current_node, "test/test2")), __LINE__,
                        __FILE__, info);
    free(absolute_path);

    destroy_node(node1);

    node1 = search_node_in_tree_with_node_creation(current_node, "test12/test42", false);
    absolute_path = get_absolute_path_of_node(node1);
    handle_string_test("/test12/test42", absolute_path, __LINE__, __FILE__, info);
    handle_boolean_test(false, are_nodes_equal(node1, search_node_in_tree(current_node, "test12/test42")), __LINE__,
                        __FILE__, info);
    handle_boolean_test(true, search_node_in_tree(current_node, "test12/test42") == NULL, __LINE__, __FILE__, info);
    free(absolute_path);

    destroy_node(node1);

    node1 = search_node_in_tree_with_node_creation(current_node, "test/test", true);
    absolute_path = get_absolute_path_of_node(node1);
    handle_string_test("/test/test", absolute_path, __LINE__, __FILE__, info);
    handle_boolean_test(false, are_nodes_equal(node1, search_node_in_tree(current_node, "test")), __LINE__, __FILE__,
                        info);
    handle_boolean_test(true, search_node_in_tree(current_node, "test/test") == NULL, __LINE__, __FILE__, info);
    free(absolute_path);

    destroy_node(node1);

    node1 = search_node_in_tree_with_node_creation(current_node, "./", false);
    handle_boolean_test(true, node1 == NULL, __LINE__, __FILE__, info);

    node1 = search_node_in_tree_with_node_creation(current_node, "../", false);
    handle_boolean_test(true, node1 == NULL, __LINE__, __FILE__, info);

    node1 = search_node_in_tree_with_node_creation(current_node, ".", false);
    handle_boolean_test(true, !is_valid_name_node(node1->name), __LINE__, __FILE__, info);
    destroy_node(node1);

    node1 = search_node_in_tree_with_node_creation(current_node, "..", false);
    handle_boolean_test(true, !is_valid_name_node(node1->name), __LINE__, __FILE__, info);
    destroy_node(node1);

    node1 = search_node_in_tree_with_node_creation(current_node, "./.././..", false);
    handle_boolean_test(true, !is_valid_name_node(node1->name), __LINE__, __FILE__, info);
    destroy_node(node1);

    node1 = search_node_in_tree_with_node_creation(current_node, "./.././../test/.", false);
    handle_boolean_test(true, !is_valid_name_node(node1->name), __LINE__, __FILE__, info);
    destroy_node(node1);

    node1 = search_node_in_tree_with_node_creation(current_node, "./.././../test/./abc_efg", false);
    handle_boolean_test(true, !is_valid_name_node(node1->name), __LINE__, __FILE__, info);
    destroy_node(node1);

    node1 = search_node_in_tree_with_node_creation(current_node, "./.././../test/", false);
    handle_boolean_test(true, node1 == NULL, __LINE__, __FILE__, info);

    node1 = search_node_in_tree_with_node_creation(current_node, "test/test/", false);
    handle_boolean_test(true, node1 == NULL, __LINE__, __FILE__, info);

    node1 = search_node_in_tree_with_node_creation(current_node, "./.././../test/new/test", false);
    handle_boolean_test(true, node1 == NULL, __LINE__, __FILE__, info);

    destroy_tree();

    current_node = NULL;
}