#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <stdio.h>

FILE *open_file(const char *path, const char *mode);
int close_file(FILE *file, const char *path);
int reset_file(const char *path);

#endif