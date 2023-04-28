#define _GNU_SOURCE
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "command.h"
#include "constants.h"
#include "file_manager.h"
#include "parser.h"
#include "string_utils.h"

/*
The maximum number of arguments for a command.
We could also use a dynamic array to store the arguments,
but for the purpose of this project, we will use a fixed size array of 2.
*/
#define MAX_COMMAND_ARGUMENTS 2

static command *get_command_from_iterator(string_iterator *);

/*
Parses a file containing commands.
The file parses lines up to MAX_LINE_LENGTH characters.
It returns 0 if the execution of the commands is successful.
*/
int parse_file(const char *path)
{
    FILE *file = open_file(path, "r");

    if (file == NULL)
    {
        return -1;
    }

    int exit_code = 0;

    if (verbose)
    {
        fputs("Parsing file ", out_stream);
        fputs(path, out_stream);
        fputs(" ...\n", out_stream);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1)
    {
        exit_code = parse_line(line);
        if (exit_code != 0)
        {
            perror("Probleme parse line");
            break;
        }
    }

    free(line);
    close_file(file, path);

    return exit_code;
}

/*
Parses a line of the file.
It returns 0 if the command execution is successful.
*/
int parse_line(char *line)
{
    string_iterator *iterator = create_string_iterator(line, ' ');

    if (iterator == NULL)
    {
        perror("Problème initialisation iterator");
        free(line);
        return -1;
    }

    command *command = get_command_from_iterator(iterator);

    if (command == NULL)
    {
        perror("Problème creation commande");
        free(line);
        return -1;
    }

    int exit_code = execute_command(command);

    destroy_string_iterator(iterator);
    destroy_command(command);

    return exit_code;
}

/*
Returns a command from a string iterator.
*/
static command *get_command_from_iterator(string_iterator *iterator)
{
    if (!has_next_word(iterator))
    {
        perror("Problème iterator vide");
        return NULL;
    }

    char *command_ = next_word(iterator);

    char **args = malloc(sizeof(char *) * MAX_COMMAND_ARGUMENTS);
    assert(args != NULL);

    int args_number = 0;
    while (has_next_word(iterator) && args_number < MAX_COMMAND_ARGUMENTS)
    {
        args[args_number] = strip_newline(next_word(iterator));
        args_number++;
    }

    if (args_number < MAX_COMMAND_ARGUMENTS)
    {
        if (args_number == 0)
        {
            free(args);
            args = NULL;
        }
        else
        {
            args = realloc(args, sizeof(char *) * args_number);
        }
    }

    return create_command(command_, args_number, args);
}
