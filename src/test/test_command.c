#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "test_core.h"
#include "../main/command.h"
#include "../main/constants.h"
#include "../main/file_manager.h"

#define N 10

static void test_write_result_command(test_info *info);
static void test_handle_number_of_args(test_info *info);

test_info *test_command()
{
    // Test setup
    print_test_header("command");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    test_write_result_command(info);
    test_handle_number_of_args(info);

    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("command", info);
    return info;
}

static void test_write_result_command(test_info *info)
{
    print_test_name("Testing to write result command in an output");

    out_stream_path = "src/test/output/test_command_write_result_empty.txt";

    out_stream = open_file(out_stream_path, "w");

    if (out_stream != NULL)
    {
        close_file(out_stream, out_stream_path);
    }

    out_stream_path = "src/test/output/test_command_write_result_1.txt";
    out_stream = open_file(out_stream_path, "w");

    if (out_stream != NULL)
    {
        handle_boolean_test(true, write_result_command("test 1212 test") == 0, __LINE__, __FILE__, info);

        close_file(out_stream, out_stream_path);
    }

    out_stream_path = "src/test/output/test_command_write_result_2.txt";
    out_stream = open_file(out_stream_path, "w");

    if (out_stream != NULL)
    {
        handle_boolean_test(true, write_result_command("test 1212 test") == 0, __LINE__, __FILE__, info);
        handle_boolean_test(true, write_result_command("test 1313 test") == 0, __LINE__, __FILE__, info);
        handle_boolean_test(true, write_result_command("test 1414 test") == 0, __LINE__, __FILE__, info);

        close_file(out_stream, out_stream_path);
    }

    out_stream_path = "src/test/output/test_command_write_result_3.txt";
    out_stream = open_file(out_stream_path, "w");

    if (out_stream != NULL)
    {
        char **results = malloc(sizeof(char *) * N);
        assert(results != NULL);

        for (unsigned i = 0; i < N; i++)
        {
            results[i] = out_stream_path;
        }

        handle_boolean_test(true, write_result_lines_command(N, results) == 0, __LINE__, __FILE__, info);

        free(results);

        close_file(out_stream, out_stream_path);
    }

    out_stream = stdout;
}

static void test_handle_number_of_args(test_info *info)
{
    print_test_name("Testing to handle the number of arguments in an output");

    out_stream_path = "src/test/output/test_command_handle_number_of_args.txt";
    out_stream = open_file(out_stream_path, "w");

    if (out_stream != NULL)
    {
        for (int i = 0; i < N + 1; ++i)
        {
            handle_boolean_test(i == (N - i), handle_number_of_args(i, N - i), __LINE__, __FILE__, info);
        }
        close_file(out_stream, out_stream_path);
    }
    out_stream = stdout;
}