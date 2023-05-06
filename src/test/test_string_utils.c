#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../main/string_utils.h"
#include "test_core.h"

static void test_string_iterator_empty(test_info *);
static void test_string_iterator_with_text(test_info *);
static void test_get_number_of_words_left(test_info *);
static void test_concat_words_with_delimiter(test_info *);
static void test_is_alphanumeric(test_info *);
static void test_starts_with(test_info *);

test_info *test_string_utils()
{
    // Test setup
    print_test_header("string utils");
    clock_t before = clock();
    test_info *info = create_test_info();

    // Add tests here
    test_string_iterator_empty(info);
    test_string_iterator_with_text(info);
    test_get_number_of_words_left(info);
    test_concat_words_with_delimiter(info);
    test_is_alphanumeric(info);
    test_starts_with(info);

    // End of tests
    info->time = clock_ticks_to_seconds(clock() - before);
    print_test_footer("string utils", info);
    return info;
}

static void test_string_iterator_empty(test_info *info)
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

static void test_string_iterator_with_text(test_info *info)
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

static void test_get_number_of_words_left(test_info *info)
{

    print_test_name("Testing concat words with delimiter");

    char *str = "";
    string_iterator *iterator = create_string_iterator(str, ' ');
    handle_int_test(0, get_number_of_words_left(iterator), __LINE__, __FILE__, info);
    destroy_string_iterator(iterator);

    str = "        ";
    iterator = create_string_iterator(str, ' ');
    handle_int_test(0, get_number_of_words_left(iterator), __LINE__, __FILE__, info);
    destroy_string_iterator(iterator);

    str = "   this    is   a test  ";
    iterator = create_string_iterator(str, ' ');
    handle_int_test(4, get_number_of_words_left(iterator), __LINE__, __FILE__, info);
    next_word(iterator);
    handle_int_test(3, get_number_of_words_left(iterator), __LINE__, __FILE__, info);
    next_word(iterator);
    handle_int_test(2, get_number_of_words_left(iterator), __LINE__, __FILE__, info);
    next_word(iterator);
    handle_int_test(1, get_number_of_words_left(iterator), __LINE__, __FILE__, info);
    next_word(iterator);
    handle_int_test(0, get_number_of_words_left(iterator), __LINE__, __FILE__, info);
    destroy_string_iterator(iterator);
}

static void test_concat_words_with_delimiter(test_info *info)
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
    assert(words != NULL);
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

static void test_starts_with(test_info *info)
{
    print_test_name("Testing starts with");

    // NULL cases
    handle_boolean_test(false, starts_with(NULL, "b"), __LINE__, __FILE__, info);
    handle_boolean_test(false, starts_with("b", NULL), __LINE__, __FILE__, info);
    handle_boolean_test(false, starts_with(NULL, NULL), __LINE__, __FILE__, info);

    // Empty cases
    handle_boolean_test(true, starts_with("", ""), __LINE__, __FILE__, info);
    handle_boolean_test(false, starts_with("", "a"), __LINE__, __FILE__, info);
    handle_boolean_test(true, starts_with("a", ""), __LINE__, __FILE__, info);

    // Positive cases
    handle_boolean_test(true, starts_with("abc", "a"), __LINE__, __FILE__, info);
    handle_boolean_test(true, starts_with("abc", "ab"), __LINE__, __FILE__, info);
    handle_boolean_test(true, starts_with("abc", "abc"), __LINE__, __FILE__, info);

    // Negative cases
    handle_boolean_test(false, starts_with("abc", "abcd"), __LINE__, __FILE__, info);
    handle_boolean_test(false, starts_with("abc", "bc"), __LINE__, __FILE__, info);
    handle_boolean_test(false, starts_with("abc", "c"), __LINE__, __FILE__, info);
    handle_boolean_test(false, starts_with("abc", "b"), __LINE__, __FILE__, info);
    handle_boolean_test(false, starts_with("abc", "ac"), __LINE__, __FILE__, info);
    handle_boolean_test(false, starts_with("abc", "abdc"), __LINE__, __FILE__, info);
}
