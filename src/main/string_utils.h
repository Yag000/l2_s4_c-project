#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdbool.h>

typedef struct a
{
    char *string;
    int index;
    char delimiter;
} string_iterator;

string_iterator *create_string_iterator(char *, char);
void destroy_string_iterator(string_iterator *);
bool has_next_string(const string_iterator *);
char *next_string(string_iterator *);

#endif