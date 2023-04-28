#include <stdio.h>
#include <stdlib.h>

#include "test_core.h"
#include "../main/constants.h"
#include "../main/tree_dir_core.h"

bool verbose = true;
bool debug;

FILE *out_stream;
char *out_stream_path;
noeud *current_node;

static void update_test_info(test_info *, test_info *);

/*
This is the main function for the test program.
Every test should be called from here and the results should be printed.
*/
int main(int argc, char *argv[])
{
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'v')
    {
        debug = true;
        puts("Debug mode enabled");
    }

    // Create the test info
    test_info *info = create_test_info();
    clock_t before = clock();

    // Add tests here

    update_test_info(info, test_string_utils());
    update_test_info(info, test_tree_dir_core());
    update_test_info(info, test_parser());
    update_test_info(info, test_command());
    update_test_info(info, test_pwd());
    update_test_info(info, test_print());

    // End of tests

    clock_t end = clock();
    info->time = clock_ticks_to_seconds(end - before);
    bool success = info->passed == info->total;

    printf("\nTotal: ");
    print_test_info(info);
    destroy_test_info(info);

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}

static void update_test_info(test_info *target_info, test_info *origin_info)
{
    target_info->passed += origin_info->passed;
    target_info->failed += origin_info->failed;
    target_info->total += origin_info->total;

    destroy_test_info(origin_info);
}