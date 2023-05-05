#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "string_utils.h"

static void update_index_to_next_word(string_iterator *);

string_iterator *create_string_iterator(char *string, char delimiter)
{
    string_iterator *iterator = malloc(sizeof(string_iterator));
    assert(iterator != NULL);
    iterator->string = string;
    iterator->index = 0;
    iterator->delimiter = delimiter;
    update_index_to_next_word(iterator);
    return iterator;
}

void destroy_string_iterator(string_iterator *iterator) { free(iterator); }

/*
Returns true if there is another word in the string.
*/
bool has_next_word(const string_iterator *iterator) { return iterator->string[iterator->index] != '\0'; }

/*
Returns the next word in the string. If there are no more words
in the string, NULL is returned.
*/
char *next_word(string_iterator *iterator)
{
    if (!has_next_word(iterator))
    {
        return NULL;
    }

    // We iterate through the string until we find a delimiter, in order to skip the word
    int start = iterator->index;
    while (iterator->string[iterator->index] != '\0' && iterator->string[iterator->index] != iterator->delimiter)
    {
        iterator->index++;
    }
    int end = iterator->index;
    update_index_to_next_word(iterator);
    int length = end - start;

    char *result = malloc(sizeof(char) * (length + 1));
    assert(result != NULL);
    result = memmove(result, iterator->string + start, length);
    assert(result != NULL);
    result[length] = '\0';

    return result;
}

/*
Updates the index to the next word in the string.
*/
static void update_index_to_next_word(string_iterator *iterator)
{
    while (iterator->string[iterator->index] != '\0' && iterator->string[iterator->index] == iterator->delimiter)
    {
        iterator->index++;
    }
}

/*
Strips the new line character from a string.
*/
void strip_newline(char *str)
{
    assert(str != NULL);

    int i, j;
    int len = strlen(str);
    for (i = j = 0; i < len; i++)
    {
        if (str[i] != '\n')
        {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}

/*
Returns the number of char in an array of arrays of char.
*/
unsigned get_number_of_char(size_t size, char **words)
{
    if (words == NULL)
    {
        return 0;
    }

    unsigned n = 0;

    for (unsigned i = 0; i < size; ++i)
    {
        n += strlen(words[i]);
    }

    return n;
}

char *concat_two_words_with_delimiter(const char *word1, const char *word2, char delimiter)
{
    char *words_concat;

    unsigned len_word1 = strlen(word1);
    unsigned len_word2 = strlen(word2);

    if (len_word1 + len_word2 == 0)
    {
        words_concat = malloc(sizeof(char));
        assert(words_concat != NULL);

        words_concat[0] = '\0';
        return words_concat;
    }

    words_concat = malloc(sizeof(char) * ((len_word1 + len_word2) + 2));
    assert(words_concat != NULL);

    memmove(words_concat, word1, len_word1);
    assert(words_concat != NULL);
    words_concat[len_word1] = delimiter;
    memmove(words_concat + len_word1 + 1, word2, len_word2);
    assert(words_concat != NULL);
    words_concat[len_word1 + len_word2 + 1] = '\0';

    return words_concat;
}

/*
Returns the string of all words concatenated, and delimited by delimiter.
*/
char *concat_words_with_delimiter(size_t size, char **words, char delimiter)
{
    char *words_concat;

    if (size <= 0 || words == NULL)
    {
        words_concat = malloc(sizeof(char));
        assert(words_concat != NULL);

        words_concat[0] = '\0';
        return words_concat;
    }

    words_concat = malloc(sizeof(char) * (get_number_of_char(size, words) + size));

    assert(words_concat != NULL);

    unsigned acc = 0;
    unsigned len_word;

    for (unsigned i = 0; i < size - 1; ++i)
    {
        len_word = strlen(words[i]);
        memmove(words_concat + acc, words[i], len_word);

        acc += len_word;
        words_concat[acc] = delimiter;
        ++acc;
    }
    len_word = strlen(words[size - 1]);
    memmove(words_concat + acc, words[size - 1], len_word);
    assert(words_concat != NULL);
    acc += len_word;

    words_concat[acc] = '\0';

    return words_concat;
}

/*
Returns true if the given string is alphanumeric.
*/
bool is_alphanumeric(const char *str)
{
    if (str == NULL || strlen(str) == 0)
    {
        return false;
    }

    for (unsigned i = 0; i < strlen(str); ++i)
    {
        if (!isalnum(str[i]))
        {
            return false;
        }
    }
    return true;
}

/*
Retuns a new pointer of string, allocated, and equal to the given string
*/
char *get_alloc_pointer_of_string(const char *s)
{
    unsigned len_s = strlen(s);
    char *result = malloc(sizeof(char) * len_s + 1);
    assert(result != NULL);

    memmove(result, s, len_s);
    assert(result != NULL);
    result[len_s] = '\0';

    return result;
}

bool starts_with(const char *str, const char *prefix)
{
    if (str == NULL || prefix == NULL)
    {
        return false;
    }

    unsigned len_str = strlen(str);
    unsigned len_prefix = strlen(prefix);

    if (len_str < len_prefix)
    {
        return false;
    }

    for (unsigned i = 0; i < len_prefix; ++i)
    {
        if (str[i] != prefix[i])
        {
            return false;
        }
    }

    return true;
}
