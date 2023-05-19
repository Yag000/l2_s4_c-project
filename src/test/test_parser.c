#include <stdio.h>

#include "../main/constants.h"
#include "../main/file_manager.h"
#include "../main/parser.h"
#include "test_core.h"

static void test_parse_file(test_info *);

test_info *test_parser()
{
    // Test setup
    print_test_header("parser");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    test_parse_file(info);

    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("parser", info);
    return info;
}

static void test_parse_file(test_info *info)
{
    out_stream_path = "src/resources/unit_tests/output/test_parser.txt";
    int error_code = -1;

    out_stream = open_file(out_stream_path, "w");

    if (out_stream == NULL)
    {
        return;
    }

    error_code = parse_file("src/resources/unit_tests/input/test_parser.txt");

    close_file(out_stream, out_stream_path);

    out_stream = stdout;

    handle_boolean_test(error_code == 0, true, __LINE__, __FILE__, info);
}
