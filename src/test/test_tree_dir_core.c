#include "test_core.h"
#include "../main/tree_dir_core.h"

void test_create_noeud(test_info *info);
void test_are_noeud_equal(test_info *info);
void test_is_fils_of_node_empty(test_info *info);
void test_append_a_fils_to_noeud(test_info *info);
void test_create_liste_noeud(test_info *info);
void test_contains_liste_noeud(test_info *info);
void test_append_liste_noeud(test_info *info);
void test_remove_liste_noeud(test_info *info);

test_info *test_tree_dir_core()
{
    print_test_header("tree dir core");

    clock_t before = clock();
    // Create the test info
    test_info *info = create_test_info();

    // Add tests here
    test_create_noeud(info);
    test_is_fils_of_node_empty(info);
    test_create_liste_noeud(info);
    test_contains_liste_noeud(info);
    test_append_liste_noeud(info);
    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    printf("Test tree dir core: ");
    print_test_info(info);
    print_test_footer("tree dir core");
    return info;
}

void test_create_noeud(test_info *info)
{
    if (verbose)
    {
        printf("\nTesting to create a node\n");
    }

    noeud *pere = create_root_noeud("pere");
    handle_boolean_test(are_noeud_equal(pere, pere->pere), true, __LINE__, __FILE__, info);
    handle_boolean_test(are_noeud_equal(pere, pere->racine), true, __LINE__, __FILE__, info);
    handle_boolean_test(pere->est_dossier, true, __LINE__, __FILE__, info);

    noeud *node = create_noeud(false, "test", pere);

    handle_boolean_test(node->est_dossier, false, __LINE__, __FILE__, info);
    handle_string_test(node->nom, "test", __LINE__, __FILE__, info);
    handle_boolean_test(are_noeud_equal(pere, node->pere), true, __LINE__, __FILE__, info);
    handle_boolean_test(are_noeud_equal(pere->racine, node->racine), true, __LINE__, __FILE__, info);
    handle_boolean_test(node->fils == NULL, true, __LINE__, __FILE__, info);

    liste_noeud *node_list = create_liste_noeud(node);
    noeud *node2 = create_noeud_with_fils(true, "test2", pere, node_list);

    handle_boolean_test(node2->est_dossier, true, __LINE__, __FILE__, info);
    handle_string_test(node2->nom, "test2", __LINE__, __FILE__, info);
    handle_boolean_test(are_noeud_equal(pere, node2->pere), true, __LINE__, __FILE__, info);
    handle_boolean_test(node2->fils != NULL, true, __LINE__, __FILE__, info);

    if (node2->fils != NULL)
    {
        handle_boolean_test(are_noeud_equal(node2->fils->no, node), true, __LINE__, __FILE__, info);
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
    if (verbose)
    {
        printf("\nTesting if fils of node is empty\n");
    }

    noeud *root = create_root_noeud("root");

    handle_boolean_test(is_fils_of_noeud_empty(root), true, __LINE__, __FILE__, info);
    noeud *node = create_noeud(false, "test", NULL);

    append_a_fils_to_noeud(root, node);
    handle_boolean_test(is_fils_of_noeud_empty(root), false, __LINE__, __FILE__, info);

    destroy_noeud(root);
}

void test_create_liste_noeud(test_info *info)
{
    if (verbose)
    {
        printf("\nTesting to create a liste noeud\n");
    }

    noeud *node = create_root_noeud("test");

    liste_noeud *node_list = create_liste_noeud(node);
    handle_boolean_test(are_noeud_equal(node, node_list->no), true, __LINE__, __FILE__, info);
    handle_boolean_test(node_list->succ == NULL, true, __LINE__, __FILE__, info);

    noeud *node2 = create_root_noeud("test2");

    handle_boolean_test(append_liste_noeud(node_list, node2), true, __LINE__, __FILE__, info);
    handle_boolean_test(node_list->succ != NULL, true, __LINE__, __FILE__, info);
    handle_boolean_test(node_list->succ->succ == NULL, true, __LINE__, __FILE__, info);
    handle_boolean_test(are_noeud_equal(node_list->succ->no, node2), true, __LINE__, __FILE__, info);

    destroy_liste_noeud(node_list);
}

void test_contains_liste_noeud(test_info *info)
{
    if (verbose)
    {
        printf("\nTesting contains liste noeud\n");
    }

    noeud *root_node = create_root_noeud("root");

    noeud *node = create_noeud(true, "test", NULL);
    handle_boolean_test(contains_liste_noeud(root_node->fils, node), false, __LINE__, __FILE__, info);
    append_a_fils_to_noeud(root_node, node);
    handle_boolean_test(contains_liste_noeud(root_node->fils, node), true, __LINE__, __FILE__, info);

    append_a_fils_to_noeud(root_node, create_noeud(false, "test2", NULL));
    append_a_fils_to_noeud(root_node, create_noeud(false, "test3", NULL));
    node = create_noeud(false, "test4", NULL);
    handle_boolean_test(contains_liste_noeud(root_node->fils, node), false, __LINE__, __FILE__, info);

    append_a_fils_to_noeud(root_node, node);
    handle_boolean_test(contains_liste_noeud(root_node->fils, node), true, __LINE__, __FILE__, info);
    append_a_fils_to_noeud(root_node, create_noeud(false, "test5", NULL));
    handle_boolean_test(contains_liste_noeud(root_node->fils, node), true, __LINE__, __FILE__, info);

    destroy_noeud(root_node);
}

void test_append_liste_noeud(test_info *info)
{
    if (verbose)
    {
        printf("\nTesting to append a node in a liste_noeud\n");
    }
    noeud *root_node = create_root_noeud("root");
    handle_boolean_test(root_node->fils == NULL, true, __LINE__, __FILE__, info);

    noeud *node = create_noeud(false, "test", NULL);
    append_a_fils_to_noeud(root_node, node);
    handle_boolean_test(root_node->fils != NULL, true, __LINE__, __FILE__, info);
    handle_boolean_test(are_noeud_equal(root_node->fils->no, node), true, __LINE__, __FILE__, info);
    handle_boolean_test(are_noeud_equal(root_node->fils->no->pere, root_node), true, __LINE__, __FILE__, info);
    handle_boolean_test(are_noeud_equal(root_node->fils->no->racine, root_node), true, __LINE__, __FILE__, info);

    node = create_noeud(false, "test2", NULL);
    handle_boolean_test(contains_liste_noeud(root_node->fils, node), false, __LINE__, __FILE__, info);
    handle_boolean_test(append_a_fils_to_noeud(root_node, node), true, __LINE__, __FILE__, info);
    handle_boolean_test(contains_liste_noeud(root_node->fils, node), true, __LINE__, __FILE__, info);
    handle_boolean_test(are_noeud_equal(node->pere, root_node), true, __LINE__, __FILE__, info);
    handle_boolean_test(are_noeud_equal(node->racine, root_node), true, __LINE__, __FILE__, info);

    append_a_fils_to_noeud(root_node, create_noeud(false, "test3", NULL));
    handle_boolean_test(contains_liste_noeud(root_node->fils, node), true, __LINE__, __FILE__, info);

    handle_boolean_test(size_liste_noeud(root_node->fils) == 3, true, __LINE__, __FILE__, info);

    destroy_noeud(root_node);
}

void test_remove_liste_noeud(test_info *info)
{
}
