#include <stdlib.h>
#include <string.h>

#include "string_utils.h"

void update_index_to_next_word(string_iterator *iterator);

string_iterator *create_string_iterator(char *string, char delimiter)
{
    string_iterator *iterator = malloc(sizeof(string_iterator));
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