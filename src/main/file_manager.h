#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <stdio.h>

FILE *open_file(const char *, const char *);
int close_file(FILE *, const char *);
int reset_file(const char *);

#endif
