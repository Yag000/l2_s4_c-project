#include <stdio.h>

#include "../main/parser.h"
#include "../main/constants.h"
#include "test_core.h"

FILE *out_stream;

void test_parse_file(test_info *info);

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

void test_parse_file(test_info *info)
{
    out_stream = fopen("src/test/output/test_parser.txt", "w");
    int error_code = -1;

    if (out_stream != NULL)
    {
        error_code = parse_file("src/test/input/test_parser.txt");
    }
    else
    {
        perror("Error while opening the file: src/test/output/test_parser.txt");
    }
    if (out_stream != NULL)
    {
        fclose(out_stream);
    }
    out_stream = stdout;

    handle_boolean_test(error_code == 0, true, __LINE__, __FILE__, info);
}
