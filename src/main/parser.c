#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "command.h"
#include "constants.h"
#include "string_utils.h"

#define MAX_LINE_LENGTH 512
// The maximum number of arguments for a command.
// We could also use a dynamic array to store the arguments,
// but for the purpose of this project, we will use a fixed size array of 2.
#define MAX_COMMAND_ARGUMENTS 2
// TODO : add documentation
command *get_command_from_iterator(string_iterator *iterator);
char *strip(char *str);
void close_file(FILE *file);

/**
 * Parses a file containing commands.
 * The file parses lines up to MAX_LINE_LENGTH characters.
 * It returns 0 if the execution of the commands is successful.
 */
int parse_file(const char *path)
{
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        char *message = malloc(sizeof(char) * (strlen("Probleme ouverture fichier ") + strlen(path) + 1));
        perror(message);
        free(message);
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int exit_code = 0;
    if (verbose)
    {
        printf("Parsing file %s ...\n", path);
    }
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
    string_iterator *iterator = create_string_iterator(line, ' ');

    if (iterator == NULL)
    {
        perror("Probleme initialisation iterator");
        return -1;
    }

    command *command = get_command_from_iterator(iterator);

    if (command == NULL)
    {
        perror("Probleme creation commande");
        return -1;
    }

    int exit_code = parse_command(command);

    destroy_string_iterator(iterator);
    destroy_command(command);

    return exit_code;
}

command *get_command_from_iterator(string_iterator *iterator)
{
    if (!has_next_word(iterator))
    {
        perror("Probleme iterator vide");
        return NULL;
    }

    char *command_ = next_word(iterator);

    char **args = malloc(sizeof(char *) * MAX_COMMAND_ARGUMENTS);
    if (args == NULL)
    {
        perror("Probleme allocation arguments");
        return NULL;
    }

    int argsNumber = 0;
    while (has_next_word(iterator) && argsNumber < MAX_COMMAND_ARGUMENTS)
    {
        args[argsNumber] = strip(next_word(iterator));
        argsNumber++;
    }

    if (argsNumber < MAX_COMMAND_ARGUMENTS)
    {
        if (argsNumber == 0)
        {
            free(args);
            args = NULL;
        }
        else
        {
            args = realloc(args, sizeof(char *) * argsNumber);
        }
    }

    return create_command(command_, argsNumber, args);
}

char *strip(char *str)
{
    int i = 0;
    int j = 0;
    while (str[i] != '\0')
    {
        if (str[i] != '\n')
        {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
    str = realloc(str, sizeof(char) * (j + 1));
    return str;
}

void close_file(FILE *file)
{
    int r = fclose(file);
    if (r != 0)
    {
        perror("Probleme fermeture de fichier");
    }
}
