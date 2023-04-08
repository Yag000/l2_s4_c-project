#include <stdlib.h>
#include <string.h>

#include "string_utils.h"

string_iterator *create_string_iterator(char *string, char delimiter)
{
    string_iterator *iterator = malloc(sizeof(string_iterator));
    iterator->string = string;
    iterator->index = 0;
    iterator->delimiter = delimiter;
    return iterator;
}

void destroy_string_iterator(string_iterator *iterator)
{
    free(iterator->string);
    free(iterator);
}

bool has_next_string_iterator(const string_iterator *iterator)
{
    return iterator->string[iterator->index] != '\0';
}

char *next_string_iterator(string_iterator *iterator)
{
    int start = iterator->index;
    while (iterator->string[iterator->index] != '\0' && iterator->string[iterator->index] != iterator->delimiter)
    {
        iterator->index++;
    }
    int end = iterator->index;
    if (iterator->string[iterator->index] != '\0')
    {
        iterator->index++;
    }
    int length = end - start;

    char *result = malloc(sizeof(char) * (length + 1));
    result = memmove(result, iterator->string + start, length);
    result[length] = '\0';

    return result;
}
