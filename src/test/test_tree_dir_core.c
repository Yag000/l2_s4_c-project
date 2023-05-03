#include <stdio.h>
#include <stdlib.h>

#include "../main/tree_dir_core.h"
#include "../main/constants.h"
#include "test_core.h"

static void test_create_noeud(test_info *);
static void test_is_valid_name_of_node(test_info *);
static void test_are_noeud_equal(test_info *);
static void test_is_root_node(test_info *);
static void test_is_fils_of_node_empty(test_info *);
static void test_create_liste_noeud(test_info *);
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
    test_create_noeud(info);
    test_is_valid_name_of_node(info);
    test_are_noeud_equal(info);
    test_is_root_node(info);
    test_is_fils_of_node_empty(info);
    test_create_liste_noeud(info);
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

static void test_create_noeud(test_info *info)
{
    print_test_name("Testing to create a node");

    noeud *pere = create_root_noeud();
    handle_boolean_test(true, are_noeuds_equal(pere, pere->pere), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(pere, pere->racine), __LINE__, __FILE__, info);
    handle_boolean_test(true, pere->est_dossier, __LINE__, __FILE__, info);

    noeud *node = create_noeud(false, "test", pere);

    handle_boolean_test(false, node->est_dossier, __LINE__, __FILE__, info);
    handle_string_test("test", node->nom, __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(pere, node->pere), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(pere->racine, node->racine), __LINE__, __FILE__, info);
    handle_boolean_test(true, node->fils == NULL, __LINE__, __FILE__, info);

    liste_noeud *node_list = create_liste_noeud(node);
    noeud *node2 = create_noeud_with_fils(true, "test2", pere, node_list);

    handle_boolean_test(true, node2->est_dossier, __LINE__, __FILE__, info);
    handle_string_test("test2", node2->nom, __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(pere, node2->pere), __LINE__, __FILE__, info);
    handle_boolean_test(true, node2->fils != NULL, __LINE__, __FILE__, info);

    if (node2->fils != NULL)
    {
        handle_boolean_test(true, are_noeuds_equal(node2->fils->no, node), __LINE__, __FILE__, info);
    }

    destroy_noeud(node2);
    destroy_noeud(pere);

    pere = create_root_noeud();

    handle_boolean_test(true, create_noeud(true, "", pere) == NULL, __LINE__, __FILE__, info);
    handle_boolean_test(true, create_noeud(true, ".", pere) == NULL, __LINE__, __FILE__, info);
    handle_boolean_test(true, create_noeud(true, "..", pere) == NULL, __LINE__, __FILE__, info);
    handle_boolean_test(true, create_noeud(true, "/", pere) == NULL, __LINE__, __FILE__, info);

    node = create_noeud(true, "name1", pere);
    handle_boolean_test(false, node == NULL, __LINE__, __FILE__, info);
    destroy_noeud(node);

    destroy_noeud(pere);
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

static void test_are_noeud_equal(test_info *info)
{
    print_test_name("Testing if two nodes are equal");

    noeud *root_node1 = create_root_noeud();
    noeud *root_node2 = create_root_noeud();

    handle_boolean_test(true, are_noeuds_equal(NULL, NULL), __LINE__, __FILE__, info);
    handle_boolean_test(false, are_noeuds_equal(root_node1, NULL), __LINE__, __FILE__, info);
    handle_boolean_test(false, are_noeuds_equal(root_node1, root_node2), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(root_node1, root_node1), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(root_node2, root_node2), __LINE__, __FILE__, info);

    noeud *node = create_noeud(false, "test", root_node1);
    append_a_fils_to_noeud(root_node1, node);
    handle_boolean_test(true, are_noeuds_equal(node, node), __LINE__, __FILE__, info);

    noeud *node2 = create_noeud(false, "test", root_node2);
    append_a_fils_to_noeud(root_node2, node2);
    handle_boolean_test(true, are_noeuds_equal(node2, node2), __LINE__, __FILE__, info);
    handle_boolean_test(false, are_noeuds_equal(node, node2), __LINE__, __FILE__, info);

    destroy_noeud(root_node1);
    destroy_noeud(root_node2);
}

static void test_is_root_node(test_info *info)
{
    print_test_name("Testing if a node is a root node");

    noeud *root_node = create_root_noeud();
    handle_boolean_test(true, is_root_node(root_node), __LINE__, __FILE__, info);

    noeud *node = create_noeud(true, "test", root_node);
    append_a_fils_to_noeud(root_node, node);
    handle_boolean_test(false, is_root_node(node), __LINE__, __FILE__, info);

    node->pere = node;
    node->racine = node;
    handle_boolean_test(false, is_root_node(node), __LINE__, __FILE__, info);

    destroy_noeud(root_node);
}

static void test_is_fils_of_node_empty(test_info *info)
{
    print_test_name("Testing if fils of node is empty");

    noeud *root = create_root_noeud();

    handle_boolean_test(true, is_fils_of_noeud_empty(root), __LINE__, __FILE__, info);
    noeud *node = create_noeud(false, "test", root);

    append_a_fils_to_noeud(root, node);
    handle_boolean_test(false, is_fils_of_noeud_empty(root), __LINE__, __FILE__, info);

    destroy_noeud(root);
}

static void test_create_liste_noeud(test_info *info)
{
    print_test_name("Testing to create a liste noeud");

    noeud *root_node = create_root_noeud();

    noeud *node = create_noeud(false, "test1", root_node);

    root_node->fils = create_liste_noeud(node);
    handle_string_test("test1", root_node->fils->no->nom, __LINE__, __FILE__, info);
    handle_boolean_test(true, root_node->fils->succ == NULL, __LINE__, __FILE__, info);

    noeud *node2 = create_noeud(false, "test2", root_node);

    handle_boolean_test(true, append_liste_noeud(root_node->fils, node2) == SUCCESS, __LINE__, __FILE__, info);
    handle_boolean_test(true, root_node->fils->succ != NULL, __LINE__, __FILE__, info);
    handle_boolean_test(true, root_node->fils->succ->succ == NULL, __LINE__, __FILE__, info);
    handle_string_test("test2", root_node->fils->succ->no->nom, __LINE__, __FILE__, info);

    destroy_noeud(root_node);
}

static void test_contains(test_info *info)
{
    print_test_name("Testing contains liste noeud");

    noeud *root_node = create_root_noeud();

    noeud *node = create_noeud(true, "test", root_node);
    handle_boolean_test(false, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);
    append_a_fils_to_noeud(root_node, node);
    handle_boolean_test(true, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);

    append_a_fils_to_noeud(root_node, create_noeud(false, "test2", root_node));
    append_a_fils_to_noeud(root_node, create_noeud(false, "test3", root_node));
    node = create_noeud(false, "test4", root_node);
    handle_boolean_test(false, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);

    append_a_fils_to_noeud(root_node, node);
    handle_boolean_test(true, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);
    append_a_fils_to_noeud(root_node, create_noeud(false, "test5", root_node));
    handle_boolean_test(true, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);

    destroy_noeud(root_node);
}

static void test_get(test_info *info)
{

    print_test_name("Testing to get a node in a liste_noeud with name");

    noeud *root_node = create_root_noeud();

    noeud *node = create_noeud(false, "test", root_node);
    append_a_fils_to_noeud(root_node, node);
    handle_boolean_test(true, are_noeuds_equal(get_a_fils_of_noeud(root_node, "test"), node), __LINE__, __FILE__, info);

    remove_a_node_from_fils(root_node, node);
    handle_boolean_test(true, get_a_fils_of_noeud(root_node, "test") == NULL, __LINE__, __FILE__, info);

    destroy_noeud(node);

    node = create_noeud(false, "test3", root_node);
    append_a_fils_to_noeud(root_node, create_noeud(false, "test1", root_node));
    append_a_fils_to_noeud(root_node, create_noeud(false, "test2", root_node));
    append_a_fils_to_noeud(root_node, node);
    append_a_fils_to_noeud(root_node, create_noeud(false, "test4", root_node));
    handle_boolean_test(true, are_noeuds_equal(get_a_fils_of_noeud(root_node, "test3"), node), __LINE__, __FILE__,
                        info);

    remove_a_node_from_fils(root_node, node);
    handle_boolean_test(true, get_a_fils_of_noeud(root_node, "test3") == NULL, __LINE__, __FILE__, info);

    destroy_noeud(node);
    destroy_noeud(root_node);
}

static void test_append(test_info *info)
{

    print_test_name("Testing to append a node in a liste_noeud");

    noeud *root_node = create_root_noeud();
    handle_boolean_test(true, root_node->fils == NULL, __LINE__, __FILE__, info);

    noeud *node = create_noeud(false, "test", root_node);
    handle_boolean_test(true, append_a_fils_to_noeud(root_node, node) == SUCCESS, __LINE__, __FILE__, info);
    handle_boolean_test(true, root_node->fils != NULL, __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(root_node->fils->no, node), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(root_node->fils->no->pere, root_node), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(root_node->fils->no->racine, root_node), __LINE__, __FILE__, info);

    node = create_noeud(false, "test2", root_node);
    handle_boolean_test(false, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);
    handle_boolean_test(true, append_a_fils_to_noeud(root_node, node) == SUCCESS, __LINE__, __FILE__, info);
    handle_boolean_test(true, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(node->pere, root_node), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(node->racine, root_node), __LINE__, __FILE__, info);

    handle_boolean_test(true, append_a_fils_to_noeud(root_node, node) == INVALID_NAME, __LINE__, __FILE__, info);

    handle_boolean_test(true, append_a_fils_to_noeud(root_node, create_noeud(false, "test3", root_node)) == SUCCESS, __LINE__, __FILE__, info);
    handle_boolean_test(true, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);

    handle_boolean_test(true, size_liste_noeud(root_node->fils) == 3, __LINE__, __FILE__, info);

    node = create_noeud(true, "test", root_node);
    handle_boolean_test(true, append_a_fils_to_noeud(root_node, node) == INVALID_NAME, __LINE__, __FILE__, info);
    free(node);

    node = create_noeud(false, "test", root_node);
    handle_boolean_test(true, append_a_fils_to_noeud(root_node, node) == INVALID_NAME, __LINE__, __FILE__, info);
    free(node);

    node = create_noeud(true, "test2", root_node);
    handle_boolean_test(true, append_a_fils_to_noeud(root_node, node) == INVALID_NAME, __LINE__, __FILE__, info);
    free(node);

    node = create_noeud(true, "test3", root_node);
    handle_boolean_test(true, append_a_fils_to_noeud(root_node, node) == INVALID_NAME, __LINE__, __FILE__, info);
    free(node);
    destroy_noeud(root_node);
}

static void test_remove(test_info *info)
{
    print_test_name("Testing to remove a node in a liste_noeud");

    noeud *root_node = create_root_noeud();

    noeud *node = create_noeud(false, "test", root_node);
    append_a_fils_to_noeud(root_node, node);
    handle_boolean_test(true, are_noeuds_equal(root_node->fils->no, node), __LINE__, __FILE__, info);

    handle_boolean_test(true, remove_a_node_from_fils(root_node, node) == SUCCESS, __LINE__, __FILE__, info);
    handle_boolean_test(true, root_node->fils == NULL, __LINE__, __FILE__, info);
    handle_boolean_test(false, remove_a_node_from_fils(root_node, node) == SUCCESS, __LINE__, __FILE__, info);

    destroy_noeud(node);

    append_a_fils_to_noeud(root_node, create_noeud(false, "test1", root_node));
    append_a_fils_to_noeud(root_node, create_noeud(false, "test2", root_node));
    node = create_noeud(false, "test3", root_node);
    append_a_fils_to_noeud(root_node, node);
    append_a_fils_to_noeud(root_node, create_noeud(false, "test4", root_node));

    handle_boolean_test(true, contains_noeud(root_node, node), __LINE__, __FILE__, info);
    handle_boolean_test(true, remove_a_node_from_fils(root_node, node) == SUCCESS, __LINE__, __FILE__, info);
    handle_boolean_test(false, contains_noeud(root_node, node), __LINE__, __FILE__, info);
    handle_boolean_test(true, remove_a_node_from_fils(root_node, node) == INVALID_SELECTION, __LINE__, __FILE__, info);

    destroy_noeud(node);
    destroy_noeud(root_node);

    root_node = create_root_noeud();
    node = create_noeud(false, "test", root_node);
    append_a_fils_to_noeud(root_node, node);

    handle_boolean_test(true, remove_a_fils_of_noeud(root_node, node->nom) == SUCCESS, __LINE__, __FILE__, info);
    handle_boolean_test(true, root_node->fils == NULL, __LINE__, __FILE__, info);
    handle_boolean_test(true, remove_a_fils_of_noeud(root_node, node->nom) == INVALID_SELECTION, __LINE__, __FILE__, info);

    destroy_noeud(root_node);

    node = create_root_noeud();
    liste_noeud *list = create_liste_noeud(node);
    handle_boolean_test(true, remove_liste_noeud(list, node) == NULL, __LINE__, __FILE__, info);

    destroy_noeud(node);
}

static void test_get_absolute_path_of_node(test_info *info)
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

static void test_search_without_create(test_info *info)
{
    print_test_name("Testing to search nodes with path without creating new nodes");
    current_node = create_basic_testing_tree();
    char *absolute_path;

    noeud *node = search_node_in_tree(current_node, "test/test2");
    absolute_path = get_absolute_path_of_node(node);
    handle_string_test("/test/test2", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node = search_node_in_tree(current_node, "test12/../test/../test12/././test13");
    absolute_path = get_absolute_path_of_node(node);
    handle_string_test("/test12/test13", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node = search_node_in_tree(current_node, "test/.././../test/./.");
    absolute_path = get_absolute_path_of_node(node);
    handle_string_test("/test", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    current_node = search_node_in_tree(current_node, "test/test5/test7");
    absolute_path = get_absolute_path_of_node(current_node);
    handle_string_test("/test/test5/test7", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node = search_node_in_tree(current_node, "..");
    absolute_path = get_absolute_path_of_node(node);
    handle_string_test("/test/test5", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node = search_node_in_tree(current_node, "../..");
    absolute_path = get_absolute_path_of_node(node);
    handle_string_test("/test", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node = search_node_in_tree(current_node, "/test12/test15");
    absolute_path = get_absolute_path_of_node(node);
    handle_string_test("/test12/test15", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node = search_node_in_tree(current_node, "/test");
    absolute_path = get_absolute_path_of_node(node);
    handle_string_test("/test", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node = search_node_in_tree(current_node, "/test/test5/.");
    absolute_path = get_absolute_path_of_node(node);
    handle_string_test("/test/test5", absolute_path, __LINE__, __FILE__, info);
    free(absolute_path);

    node = search_node_in_tree(current_node, "");
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

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

    node = search_node_in_tree(current_node, "/test12/test13/..");
    handle_boolean_test(true, node == NULL, __LINE__, __FILE__, info);

    destroy_tree();

    current_node = NULL;
}

static void test_search_with_create(test_info *info)
{
    print_test_name("Testing to search nodes with path with creating new nodes");
    current_node = create_basic_testing_tree();
    char *absolute_path;

    noeud *node = search_node_in_tree_with_node_creation(current_node, "test/test2", false);
    absolute_path = get_absolute_path_of_node(node);
    handle_string_test("/test/test2", absolute_path, __LINE__, __FILE__, info);
    handle_boolean_test(false, are_noeuds_equal(node, search_node_in_tree(current_node, "test/test2")), __LINE__, __FILE__, info);
    free(absolute_path);

    destroy_noeud(node);

    node = search_node_in_tree_with_node_creation(current_node, "test12/test42", false);
    absolute_path = get_absolute_path_of_node(node);
    handle_string_test("/test12/test42", absolute_path, __LINE__, __FILE__, info);
    handle_boolean_test(false, are_noeuds_equal(node, search_node_in_tree(current_node, "test12/test42")), __LINE__, __FILE__, info);
    handle_boolean_test(true, search_node_in_tree(current_node, "test12/test42") == NULL, __LINE__, __FILE__, info);
    free(absolute_path);

    destroy_noeud(node);

    node = search_node_in_tree_with_node_creation(current_node, "test/test", true);
    absolute_path = get_absolute_path_of_node(node);
    handle_string_test("/test/test", absolute_path, __LINE__, __FILE__, info);
    handle_boolean_test(false, are_noeuds_equal(node, search_node_in_tree(current_node, "test")), __LINE__, __FILE__, info);
    handle_boolean_test(true, search_node_in_tree(current_node, "test/test") == NULL, __LINE__, __FILE__, info);
    free(absolute_path);

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