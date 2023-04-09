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
    noeud *node = create_noeud(false, "test", pere);

    handle_boolean_test(node->est_dossier, false, __LINE__, __FILE__, info);
    handle_string_test(node->nom, "test", __LINE__, __FILE__, info);
    handle_boolean_test(are_noeud_equal(pere, node->pere), true, __LINE__, __FILE__, info);
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
}

void test_append_a_fils_to_noeud(test_info *info)
{
}

void test_create_liste_noeud(test_info *info)
{
}

void test_contains_liste_noeud(test_info *info)
{
}

void test_append_liste_noeud(test_info *info)
{
}

void test_remove_liste_noeud(test_info *info)
{
}
