#include <stdio.h>
#include <stdlib.h>

#include "test_core.h"
#include "../main/tree_dir_core.h"

void test_create_noeud(test_info *info);
void test_is_fils_of_node_empty(test_info *info);
void test_create_liste_noeud(test_info *info);
void test_contains(test_info *info);
void test_get(test_info *info);
void test_append(test_info *info);
void test_remove(test_info *info);

test_info *test_tree_dir_core()
{
    // Test setup
    print_test_header("tree dir core");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    test_create_noeud(info);
    test_is_fils_of_node_empty(info);
    test_create_liste_noeud(info);
    test_contains(info);
    test_get(info);
    test_append(info);
    test_remove(info);

    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("tree dir core", info);
    return info;
}

void test_create_noeud(test_info *info)
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
}

void test_are_noeud_equal(test_info *info)
{
    // TODO
}

void test_is_fils_of_node_empty(test_info *info)
{
    print_test_name("Testing if fils of node is empty");

    noeud *root = create_root_noeud();

    handle_boolean_test(true, is_fils_of_noeud_empty(root), __LINE__, __FILE__, info);
    noeud *node = create_noeud(false, "test", NULL);

    append_a_fils_to_noeud(root, node);
    handle_boolean_test(false, is_fils_of_noeud_empty(root), __LINE__, __FILE__, info);

    destroy_noeud(root);
}

void test_create_liste_noeud(test_info *info)
{
    print_test_name("Testing to create a liste noeud");

    noeud *node = create_noeud(false, "test1", NULL);

    liste_noeud *node_list = create_liste_noeud(node);
    handle_boolean_test(true, are_noeuds_equal(node, node_list->no), __LINE__, __FILE__, info);
    handle_boolean_test(true, node_list->succ == NULL, __LINE__, __FILE__, info);

    noeud *node2 = create_root_noeud(false, "test2", NULL);

    handle_boolean_test(true, append_liste_noeud(node_list, node2), __LINE__, __FILE__, info);
    handle_boolean_test(true, node_list->succ != NULL, __LINE__, __FILE__, info);
    handle_boolean_test(true, node_list->succ->succ == NULL, __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(node_list->succ->no, node2), __LINE__, __FILE__, info);

    destroy_liste_noeud(node_list);
}

void test_contains(test_info *info)
{
    print_test_name("Testing contains liste noeud");

    noeud *root_node = create_root_noeud();

    noeud *node = create_noeud(true, "test", NULL);
    handle_boolean_test(false, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);
    append_a_fils_to_noeud(root_node, node);
    handle_boolean_test(true, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);

    append_a_fils_to_noeud(root_node, create_noeud(false, "test2", NULL));
    append_a_fils_to_noeud(root_node, create_noeud(false, "test3", NULL));
    node = create_noeud(false, "test4", NULL);
    handle_boolean_test(false, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);

    append_a_fils_to_noeud(root_node, node);
    handle_boolean_test(true, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);
    append_a_fils_to_noeud(root_node, create_noeud(false, "test5", NULL));
    handle_boolean_test(true, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);

    destroy_noeud(root_node);
}

void test_get(test_info *info)
{

    print_test_name("Testing to get a node in a liste_noeud with name");

    noeud *root_node = create_root_noeud();

    noeud *node = create_noeud(false, "test", NULL);
    append_a_fils_to_noeud(root_node, node);
    handle_boolean_test(true, are_noeuds_equal(get_a_fils_of_noeud(root_node, "test"), node), __LINE__, __FILE__, info);

    remove_a_node_from_fils(root_node, node);
    handle_boolean_test(true, get_a_fils_of_noeud(root_node, "test") == NULL, __LINE__, __FILE__, info);

    destroy_noeud(node);

    node = create_noeud(false, "test3", NULL);
    append_a_fils_to_noeud(root_node, create_noeud(false, "test1", NULL));
    append_a_fils_to_noeud(root_node, create_noeud(false, "test2", NULL));
    append_a_fils_to_noeud(root_node, node);
    append_a_fils_to_noeud(root_node, create_noeud(false, "test4", NULL));
    handle_boolean_test(true, are_noeuds_equal(get_a_fils_of_noeud(root_node, "test3"), node), __LINE__, __FILE__, info);

    remove_a_node_from_fils(root_node, node);
    handle_boolean_test(true, get_a_fils_of_noeud(root_node, "test3") == NULL, __LINE__, __FILE__, info);

    destroy_noeud(node);
    destroy_noeud(root_node);
}

void test_append(test_info *info)
{

    print_test_name("Testing to append a node in a liste_noeud");

    noeud *root_node = create_root_noeud();
    handle_boolean_test(true, root_node->fils == NULL, __LINE__, __FILE__, info);

    noeud *node = create_noeud(false, "test", NULL);
    append_a_fils_to_noeud(root_node, node);
    handle_boolean_test(true, root_node->fils != NULL, __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(root_node->fils->no, node), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(root_node->fils->no->pere, root_node), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(root_node->fils->no->racine, root_node), __LINE__, __FILE__, info);

    node = create_noeud(false, "test2", NULL);
    handle_boolean_test(false, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);
    handle_boolean_test(true, append_a_fils_to_noeud(root_node, node), __LINE__, __FILE__, info);
    handle_boolean_test(true, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(node->pere, root_node), __LINE__, __FILE__, info);
    handle_boolean_test(true, are_noeuds_equal(node->racine, root_node), __LINE__, __FILE__, info);

    handle_boolean_test(append_a_fils_to_noeud(root_node, node), false, __LINE__, __FILE__, info);

    append_a_fils_to_noeud(root_node, create_noeud(false, "test3", NULL));
    handle_boolean_test(true, contains_liste_noeud(root_node->fils, node), __LINE__, __FILE__, info);

    handle_boolean_test(true, size_liste_noeud(root_node->fils) == 3, __LINE__, __FILE__, info);

    destroy_noeud(root_node);
}

void test_remove(test_info *info)
{
    print_test_name("Testing to remove a node in a liste_noeud");

    noeud *root_node = create_root_noeud();

    noeud *node = create_noeud(false, "test", NULL);
    append_a_fils_to_noeud(root_node, node);
    handle_boolean_test(true, are_noeuds_equal(root_node->fils->no, node), __LINE__, __FILE__, info);

    handle_boolean_test(true, remove_a_node_from_fils(root_node, node), __LINE__, __FILE__, info);
    handle_boolean_test(true, root_node->fils == NULL, __LINE__, __FILE__, info);
    handle_boolean_test(false, remove_a_node_from_fils(root_node, node), __LINE__, __FILE__, info);

    destroy_noeud(node);

    append_a_fils_to_noeud(root_node, create_noeud(false, "test1", NULL));
    append_a_fils_to_noeud(root_node, create_noeud(false, "test2", NULL));
    node = create_noeud(false, "test3", NULL);
    append_a_fils_to_noeud(root_node, node);
    append_a_fils_to_noeud(root_node, create_noeud(false, "test4", NULL));

    handle_boolean_test(true, contains_noeud(root_node, node), __LINE__, __FILE__, info);
    handle_boolean_test(true, remove_a_node_from_fils(root_node, node), __LINE__, __FILE__, info);
    handle_boolean_test(false, contains_noeud(root_node, node), __LINE__, __FILE__, info);
    handle_boolean_test(false, remove_a_node_from_fils(root_node, node), __LINE__, __FILE__, info);

    destroy_noeud(node);
    destroy_noeud(root_node);

    root_node = create_root_noeud();
    node = create_noeud(false, "test", NULL);
    append_a_fils_to_noeud(root_node, node);

    handle_boolean_test(true, remove_a_fils_of_noeud(root_node, node->nom), __LINE__, __FILE__, info);
    handle_boolean_test(true, root_node->fils == NULL, __LINE__, __FILE__, info);
    handle_boolean_test(false, remove_a_fils_of_noeud(root_node, node->nom), __LINE__, __FILE__, info);

    destroy_noeud(root_node);

    node = create_noeud(false, "test", NULL);
    liste_noeud *list = create_liste_noeud(node);
    handle_boolean_test(true, remove_liste_noeud(list, node) == NULL, __LINE__, __FILE__, info);

    destroy_noeud(node);
}
