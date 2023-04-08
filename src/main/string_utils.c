#include <stdlib.h>
#include <string.h>

// TODO: remove this
#include <stdio.h>

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

bool has_next_string(const string_iterator *iterator)
{
    return iterator->string[iterator->index] != '\0';
}

char *next_string(string_iterator *iterator)
{
    if (!has_next_string(iterator))
    {
        return NULL;
    }

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
void update_index_to_next_word(string_iterator *iterator)
{
    while (iterator->string[iterator->index] != '\0' && iterator->string[iterator->index] == iterator->delimiter)
    {
        iterator->index++;
    }
}