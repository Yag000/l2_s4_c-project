#include "test_core.h"

#include "../main/file_manager.h"
#include "../main/tree_dir_core.h"
#include "../main/command.h"
#include "../main/constants.h"

void test_go_to_root(test_info *);
void test_go_to_previous_directory(test_info *);
void test_invalid_invalid_number_args(test_info *);
void test_invalid_path(test_info *);
void test_valid_paths(test_info *);

static void init_folder_struture();

test_info *test_cd()
{
    // Test setup
    print_test_header("cd");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    init_folder_struture();
    test_go_to_root(info);
    test_go_to_previous_directory(info);
    test_invalid_path(info);
    test_valid_paths(info);

    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("cd", info);
    return info;
}

void test_go_to_root(test_info *info) {

    print_test_name("Testing cd to root");
    
        
}
void test_go_to_previous_directory(test_info *info) {}
void test_invalid_invalid_number_args(test_info *info) {}
void test_invalid_path(test_info *info) {}
void test_valid_paths(test_info *info) {}



static void init_folder_struture(){

    out_stream_path = "src/test/output/test_print.txt";
    out_stream = open_file(out_stream_path, "w");

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

    append_a_fils_to_noeud(root, create_noeud(false, "test9", root));
    append_a_fils_to_noeud(root, create_noeud(true, "test10", root));

    node1 = create_noeud(true, "test11", root);
    append_a_fils_to_noeud(root, node1);

    append_a_fils_to_noeud(node1, create_noeud(false, "test12", node1));

}
