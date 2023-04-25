#include <stdio.h>

#include "../main/parser.h"
#include "../main/constants.h"
#include "../main/file_manager.h"
#include "test_core.h"

FILE *out_stream;
char *out_stream_path = "src/test/output/test_parser.txt";

void test_parse_file(test_info *info);

test_info *test_parser()
{
    print_test_header("parser");
    clock_t before = clock();
    test_info *info = create_test_info();

    test_parse_file(info);

    info->time = clock_ticks_to_seconds(clock() - before);
    printf("Test parser: ");
    print_test_info(info);
    print_test_footer("parser");
    return info;
}

void test_parse_file(test_info *info)
{
    int error_code = -1;

    if (reset_file(out_stream_path) == 0)
    {
        out_stream = open_file(out_stream_path, "a");

        if (out_stream == NULL)
        {
            return;
        }

        error_code = parse_file("src/test/input/test_parser.txt");

        close_file(out_stream, out_stream_path);
    }

    out_stream = stdout;

    handle_boolean_test(error_code == 0, true, __LINE__, __FILE__, info);
}
