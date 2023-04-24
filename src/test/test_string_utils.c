#include <stdio.h>
#include <stdlib.h>

#include "test_core.h"
#include "../main/string_utils.h"

void test_string_iterator_empty(test_info *info);
void test_string_iterator_with_text(test_info *info);
void test_concat_words_with_delimiter(test_info *info);
static void test_is_alphanumeric(test_info *info);

test_info *test_string_utils()
{
    print_test_header("string utils");

    clock_t before = clock();
    // Create the test info
    test_info *info = create_test_info();

    // Add tests here
    test_string_iterator_empty(info);
    test_string_iterator_with_text(info);
    test_concat_words_with_delimiter(info);
    test_is_alphanumeric(info);

    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    printf("Test string utils: ");
    print_test_info(info);
    print_test_footer("string utils");
    return info;
}

void test_string_iterator_empty(test_info *info)
{
    print_test_name("Testing string iterator with empty string");

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
    print_test_name("Testing string iterator with text");

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

void test_concat_words_with_delimiter(test_info *info)
{
    print_test_name("Testing concat words with delimiter");

    char *c = concat_two_words_with_delimiter("", "", '/');
    handle_string_test("", c, __LINE__, __FILE__, info);

    free(c);

    c = concat_two_words_with_delimiter("abc", "efg", 'd');
    handle_string_test("abcdefg", c, __LINE__, __FILE__, info);

    free(c);

    c = concat_two_words_with_delimiter("/path/of/directory", "file", '/');
    handle_string_test("/path/of/directory/file", c, __LINE__, __FILE__, info);

    free(c);

    c = concat_words_with_delimiter(0, NULL, '/');
    handle_string_test("", c, __LINE__, __FILE__, info);

    free(c);

    size_t size_words = 4;

    char **words = malloc(size_words * sizeof(char *));
    words[0] = "ab";
    words[1] = "bc";
    words[2] = "cd";
    words[3] = "de";

    c = concat_words_with_delimiter(size_words, words, '/');
    handle_string_test("ab/bc/cd/de", c, __LINE__, __FILE__, info);

    words[0] = "";
    words[1] = "";
    words[2] = "";
    words[3] = "";

    free(c);

    c = concat_words_with_delimiter(size_words, words, '/');
    handle_string_test("///", c, __LINE__, __FILE__, info);

    free(c);

    words[0] = "";
    words[1] = "path";
    words[2] = "of";
    words[3] = "directory";

    c = concat_words_with_delimiter(size_words, words, '/');
    handle_string_test("/path/of/directory", c, __LINE__, __FILE__, info);

    free(c);
    free(words);
}

static void test_is_alphanumeric(test_info *info)
{
    print_test_name("Testing is alphanumeric");

    // Single character
    handle_boolean_test(true, is_alphanumeric("a"), __LINE__, __FILE__, info);
    handle_boolean_test(true, is_alphanumeric("z"), __LINE__, __FILE__, info);
    handle_boolean_test(true, is_alphanumeric("A"), __LINE__, __FILE__, info);
    handle_boolean_test(true, is_alphanumeric("Z"), __LINE__, __FILE__, info);
    handle_boolean_test(true, is_alphanumeric("0"), __LINE__, __FILE__, info);
    handle_boolean_test(true, is_alphanumeric("9"), __LINE__, __FILE__, info);
    handle_boolean_test(false, is_alphanumeric(" "), __LINE__, __FILE__, info);
    handle_boolean_test(false, is_alphanumeric("\\"), __LINE__, __FILE__, info);
    handle_boolean_test(false, is_alphanumeric(""), __LINE__, __FILE__, info);
    handle_boolean_test(false, is_alphanumeric(NULL), __LINE__, __FILE__, info);

    // Multiple characters
    handle_boolean_test(true, is_alphanumeric("abc"), __LINE__, __FILE__, info);
    handle_boolean_test(true, is_alphanumeric("ABC"), __LINE__, __FILE__, info);
    handle_boolean_test(true, is_alphanumeric("123"), __LINE__, __FILE__, info);
    handle_boolean_test(true, is_alphanumeric("1a3"), __LINE__, __FILE__, info);
    handle_boolean_test(true, is_alphanumeric("1ADS"), __LINE__, __FILE__, info);
    handle_boolean_test(false, is_alphanumeric("-3"), __LINE__, __FILE__, info);
    handle_boolean_test(false, is_alphanumeric("das123das\\"), __LINE__, __FILE__, info);
    handle_boolean_test(false, is_alphanumeric(".123-"), __LINE__, __FILE__, info);
}
