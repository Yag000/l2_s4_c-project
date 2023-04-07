#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

#define MAX_LINE_LENGTH 512
void close_file(FILE *file);

/**
 * Parses a file containing commands.
 * The file parses lines up to MAX_LINE_LENGTH characters.
 * It returns 0 if the execution of the commands is successful.
 */
int parse_file(char *path)
{

    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        perror("Probleme ouverture de fichier");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int exit_code = 0;

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        exit_code = parse_line(line);
        if (exit_code != 0)
        {
            perror("Probleme parse line");
            break;
        }
    }

    close_file(file);

    return exit_code;
}

/**
 * Parses a line of the file.
 * It returns 0 if the command is valid.
 */
int parse_line(char *line)
{
    // TODO
    return 0;
}

void close_file(FILE *file)
{
    int r = fclose(file);
    if (r != 0)
    {
        perror("Probleme fermeture de fichier");
    }
}
