#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "file_manager.h"

static void print_error_message(const char *, const char *);

/*
Opens the stream, send an error message if it fails
*/
FILE *open_file(const char *path, const char *mode)
{
    if (path == NULL)
    {
        print_error_message("Failure while opening the file:the path was NULL", "");
        return NULL;
    }
    FILE *file = fopen(path, mode);
    if (file == NULL)
    {
        print_error_message("Failure while opening: ", path);
    }
    return file;
}

/*
Closes the stream, send an error message if it fails
*/
int close_file(FILE *file, const char *path)
{
    int exit_code = fclose(file);

    if (exit_code != 0)
    {
        print_error_message("Failure while closing: ", path);
        return FATAL_ERROR;
    }
    return SUCCESS;
}

/*
   Prints the error message and the path of the file where it happened an error
*/
static void print_error_message(const char *error_message, const char *path)
{
    if (error_message == NULL || path == NULL)
    {
        return;
    }

    fprintf(out_stream, "%s %s\n", error_message, path);
}
