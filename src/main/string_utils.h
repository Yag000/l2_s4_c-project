#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdbool.h>

/**
 * A string iterator that can be used to iterate over a string
 * with a given delimiter. It will return the next word in the
 * string until there are no more words left. A word is
 * defined as a string between two delimiters or between a delimiter
 * and the start/end of the string.
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

char *strip_newline(char *string);

unsigned get_number_of_char(size_t size, char **words);
char *concat_two_words_with_delimiter(const char *word1, const char *word2, char delimiter);
char *concat_words_with_delimiter(size_t size, char **words, char delimiter);

bool is_alphanumeric(const char *);

#endif