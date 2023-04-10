#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "string_utils.h"

void update_index_to_next_word(string_iterator *iterator);
unsigned get_number_of_char(size_t size, char **words);

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

void destroy_string_iterator(string_iterator *iterator)
{
    free(iterator);
}

/**
 * Returns true if there is another word in the string.
 */
bool has_next_word(const string_iterator *iterator)
{
    return iterator->string[iterator->index] != '\0';
}

/**
 * Returns the next word in the string. If there are no more words
 * in the string, NULL is returned.
 */
char *next_word(string_iterator *iterator)
{
    if (!has_next_word(iterator))
    {
        return NULL;
    }

    // We iterate through the string until we find a delimiter, i order to skip the word
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
    result[length] = '\0';

    return result;
}

/**
 * Updates the index to the next word in the string.
 */
void update_index_to_next_word(string_iterator *iterator)
{
    while (iterator->string[iterator->index] != '\0' && iterator->string[iterator->index] == iterator->delimiter)
    {
        iterator->index++;
    }
}

/**
 * Strips the new line character from a string.
 */
char *strip_newline(char *str)
{
    int i = 0;
    int j = 0;
    while (str[i] != '\0')
    {
        if (str[i] != '\n')
        {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
    str = realloc(str, sizeof(char) * (j + 1));
    return str;
}

/**
 * Return the number of char in an array of array of char
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

    words_concat = malloc(sizeof(char) * (len_word1 + len_word2) + 2);
    assert(words_concat != NULL);

    memmove(words_concat, word1, len_word1);
    words_concat[len_word1] = delimiter;
    memmove(words_concat + len_word1 + 1, word2, len_word2);
    words_concat[len_word1 + len_word2 + 1] = '\0';

    return words_concat;
}

/**
 * Return the string of all words concatenated, and delimited by delimiter
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

    words_concat = malloc(sizeof(char) * get_number_of_char(size, words) + size);

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
    acc += len_word;

    words_concat[acc] = '\0';

    return words_concat;
}