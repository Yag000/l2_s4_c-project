#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdbool.h>

/*
A string iterator that can be used to iterate over a string
with a given delimiter. It will return the next word in the
string until there are no more words left. A word is
defined as a string between two delimiters or between a delimiter
and the start/end of the string.
*/
typedef struct string_iterator
{
    char *string;
    int index;
    char delimiter;
} string_iterator;

string_iterator *create_string_iterator(char *, char);
void destroy_string_iterator(string_iterator *);
bool has_next_word(const string_iterator *);
char *next_word(string_iterator *);
int get_number_of_words_left(const string_iterator *);

void strip_newline(char *);

unsigned get_number_of_char(size_t, char **);
char *concat_two_words_with_delimiter(const char *, const char *, char);
char *concat_words_with_delimiter(size_t, char **, char);

bool is_alphanumeric(const char *);
char *get_alloc_pointer_of_string(const char *);

bool starts_with(const char *, const char *);

#endif
