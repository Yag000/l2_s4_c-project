#include "test_core.h"
#include "../main/string_utils.h"

void test_string_iterator_empty(test_info *info);
void test_string_iterator_with_text(test_info *info);

test_info *test_string_utils()
{
    print_test_header("string utils");

    clock_t before = clock();
    // Create the test info
    test_info *info = create_test_info();

    // Add tests here
    test_string_iterator_empty(info);
    test_string_iterator_with_text(info);
    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    printf("Test string utils: ");
    print_test_info(info);
    print_test_footer("string utils");
    return info;
}

void test_string_iterator_empty(test_info *info)
{

    if (verbose)
    {
        printf("\nTesting string iterator with empty string \n");
    }
    char *str = "     ";

    string_iterator *iterator = create_string_iterator(str, ' ');

    handle_boolean_test(false, has_next_word(iterator), __LINE__, __FILE__, info);

    destroy_string_iterator(iterator);

    str = "";

    iterator = create_string_iterator(str, ' ');

    handle_boolean_test(false, has_next_word(iterator), __LINE__, __FILE__, info);

    destroy_string_iterator(iterator);
}

void test_string_iterator_with_text(test_info *info)
{
    if (verbose)
    {
        printf("\nTesting string iterator with text \n");
    }

    char *str = "   this    is   a test  ";

    string_iterator *iterator = create_string_iterator(str, ' ');

    char *current_string = next_word(iterator);
    handle_string_test("this", current_string, __LINE__, __FILE__, info);
    free(current_string);

    current_string = next_word(iterator);
    handle_string_test("is", current_string, __LINE__, __FILE__, info);
    free(current_string);

    current_string = next_word(iterator);
    handle_string_test("a", current_string, __LINE__, __FILE__, info);
    free(current_string);

    current_string = next_word(iterator);
    handle_string_test("test", current_string, __LINE__, __FILE__, info);
    free(current_string);

    handle_boolean_test(false, has_next_word(iterator), __LINE__, __FILE__, info);

    destroy_string_iterator(iterator);

    str = "cd   ../test/test/test.c";

    iterator = create_string_iterator(str, ' ');

    current_string = next_word(iterator);
    handle_string_test("cd", current_string, __LINE__, __FILE__, info);
    free(current_string);

    current_string = next_word(iterator);
    handle_string_test("../test/test/test.c", current_string, __LINE__, __FILE__, info);
    free(current_string);

    handle_boolean_test(false, has_next_word(iterator), __LINE__, __FILE__, info);

    destroy_string_iterator(iterator);
}
