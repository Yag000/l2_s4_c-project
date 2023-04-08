#include "test_core.h"
#include "../main/string_utils.h"

void test_string_iterator(test_info *info);

test_info *test_string_utils()
{
    clock_t before = clock();
    // Create the test info
    test_info *info = create_test_info();

    // Add tests here
    test_string_iterator(info);
    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    printf("Test string utils: ");
    print_test_info(info);
    return info;
}

void test_string_iterator(test_info *info)
{

    char *str = "   this    is   a test  ";

    string_iterator *iterator = create_string_iterator(str, ' ');

    char *current_string = next_string(iterator);
    handle_string_test("this", current_string, __LINE__, __FILE__, info);

    current_string = next_string(iterator);
    handle_string_test("is", current_string, __LINE__, __FILE__, info);

    current_string = next_string(iterator);
    handle_string_test("a", current_string, __LINE__, __FILE__, info);

    current_string = next_string(iterator);
    handle_string_test("test", current_string, __LINE__, __FILE__, info);

    if (has_next_string(iterator))
    {
        printf("Error: has_next_string should return false at line %d in file %s \n", __LINE__, __FILE__);
        info->failed++;
    }
    else
    {
        info->passed++;
    }
    info->total++;

    destroy_string_iterator(iterator);

    str = "     ";

    iterator = create_string_iterator(str, ' ');

    if (has_next_string(iterator))
    {
        printf("Error: has_next_string should return false at line %d in file %s \n", __LINE__, __FILE__);
        info->failed++;
    }
    else
    {
        info->passed++;
    }

    info->total++;

    destroy_string_iterator(iterator);
}
