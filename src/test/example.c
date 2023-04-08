/**
 * This is an example of how to write a test.
 * The test should be added to the main function in test.c
 *
 * A test could consist on getting a file, computing something
 * and writing the result to another file. For example we could have
 * a file that contains instructions and we output the result of the
 * execution of those instructions.
 */

#include "test_core.h"

bool test1();
bool test2();
bool test3();

test_info *test_example()
{
    clock_t before = clock();
    // Create the test info
    test_info *info = create_test_info();

    // Add tests here

    test1() ? info->passed++ : info->failed++;
    info->total++;

    test2() ? info->passed++ : info->failed++;
    info->total++;

    test3() ? info->passed++ : info->failed++;
    info->total++;

    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    printf("Test example: ");
    print_test_info(info);
    return info;
}

bool test1()
{

    // Get date from the file "src/test/input/Example.txt"
    // Compute something
    if (verbose)
    {
        // Print information about the test
    }
    // Write the end result to the file "src/test/output/Example.txt"

    return true;
}

bool test2()
{
    // A test
    return 1 + 1 == 2;
}

bool test3()
{
    // Another test
    return true;
}