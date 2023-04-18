#include "test_core.h"

void update_test_info(test_info *target_info, test_info *origin_info);
bool verbose;
/**
 * This is the main function for the test program.
 * Every test should be called from here and the results should be printed.
 *
 */
int main(int argc, char *argv[])
{
    if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'v')
    {
        verbose = true;
        puts("Verbose mode enabled");
    }

    // Create the test info
    test_info *info = create_test_info();
    clock_t before = clock();

    // Add tests here

    update_test_info(info, test_string_utils());
    update_test_info(info, test_tree_dir_core());
    update_test_info(info, test_parser());

    // End of tests

    clock_t end = clock();
    info->time = clock_ticks_to_seconds(end - before);
    bool success = info->passed == info->total;

    printf("\nTotal: ");
    print_test_info(info);
    destroy_test_info(info);

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}

void update_test_info(test_info *target_info, test_info *origin_info)
{
    target_info->passed += origin_info->passed;
    target_info->failed += origin_info->failed;
    target_info->total += origin_info->total;

    destroy_test_info(origin_info);
}