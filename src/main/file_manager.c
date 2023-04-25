#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "file_manager.h"

void print_error_message(const char *error_message, const char *path);

/*
Opens the stream, send an error message if it fails
*/
FILE *open_file(const char *path, const char *mode)
{
    FILE *file = fopen(path, mode);
    if (file == NULL)
    {
        print_error_message("Problème ouverture fichier ", path);
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
        print_error_message("Problème fermeture fichier ", path);
        return -1;
    }
    return 0;
}

/*
Resets the file at path
*/
int reset_file(const char *path)
{
    FILE *file_to_reset = open_file(path, "w");

    if (file_to_reset == NULL)
    {
        return -1;
    }

    return fclose(file_to_reset);
}

/*
Prints the error message and the path of the file where it happened an error
*/
void print_error_message(const char *error_message, const char *path)
{
    char *message = malloc(sizeof(char) * (strlen(error_message) + strlen(path) + 1));
    assert(message != NULL);
    message = strcat(message, error_message);
    message = strcat(message, path);
    perror(message);
    free(message);
}
