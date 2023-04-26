#include <stdio.h>
#include <stdlib.h>

#include "test_core.h"
#include "../main/command.h"
#include "../main/constants.h"
#include "../main/tree_dir_core.h"
#include "../main/file_manager.h"
#include "../main/string_utils.h"

void test_print_function(test_info *info);

test_info *test_print()
{
    print_test_header("print");

    clock_t before = clock();
    // Create the test info
    test_info *info = create_test_info();

    // Add tests here
    test_print_function(info);
    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("pwd", info);
    return info;
}

void test_print_function(test_info *info)
{
    print_test_name("Testing command print");

    out_stream_path = "src/test/output/test_print.txt";
    out_stream = open_file(out_stream_path, "w");

    command *c = create_command(get_alloc_pointer_of_string("print"), 0, malloc(0));

    noeud *root = create_root_noeud();
    current_node = root;

    execute_command(c);

    noeud *node1 = create_noeud(true, "test", root);
    append_a_fils_to_noeud(root, node1);

    append_a_fils_to_noeud(node1, create_noeud(false, "test2", node1));
    append_a_fils_to_noeud(node1, create_noeud(true, "test3", node1));
    append_a_fils_to_noeud(node1, create_noeud(false, "test4", node1));

    noeud *node2 = create_noeud(true, "test5", node1);
    append_a_fils_to_noeud(node1, node2);

    execute_command(c);

    append_a_fils_to_noeud(node2, create_noeud(false, "test6", node2));
    append_a_fils_to_noeud(node2, create_noeud(true, "test7", node2));
    append_a_fils_to_noeud(node2, create_noeud(false, "test8", node2));

    append_a_fils_to_noeud(root, create_noeud(false, "test9", root));
    append_a_fils_to_noeud(root, create_noeud(true, "test10", root));

    node1 = create_noeud(true, "test11", root);
    append_a_fils_to_noeud(root, node1);

    append_a_fils_to_noeud(node1, create_noeud(false, "test12", node1));

    execute_command(c);

    destroy_command(c);
    destroy_noeud(root);
}