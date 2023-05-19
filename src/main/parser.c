#define _GNU_SOURCE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "command.h"
#include "constants.h"
#include "file_manager.h"
#include "parser.h"
#include "string_utils.h"

static bool should_program_stop(int);

/*
Parses a file containing commands.
The file parses lines up to MAX_LINE_LENGTH characters.
It returns 0 if the execution of the commands is successful.
*/
int parse_file(const char *path)
{
    if (verbose && !interactive)
    {
        fputs("Parsing file ", out_stream);
        fputs(path, out_stream);
        fputs(" ...\n", out_stream);
    }

    FILE *file;
    if (interactive)
    {

        file = stdin;
    }
    else
    {
        file = open_file(path, "r");
    }

    if (file == NULL)
    {
        return FATAL_ERROR;
    }

    if (interactive)
    {
        print_command_header_with_stream(stdout);
    }

    int exit_code = SUCCESS;

    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1)
    {
        exit_code = parse_line(line);

        if (should_program_stop(exit_code))
        {
            break;
        }
        if (interactive)
        {
            print_command_header_with_stream(stdout);
        }
    }

    free(line);

    fclose(file);

    if (!error_occurs_stop)
    {
        return SUCCESS;
    }

    return exit_code;
}

static bool should_program_stop(int exit_code)
{
    // We consider an empty command as a valid one and thus we do not stop the program
    if (error_occurs_stop && exit_code != SUCCESS && exit_code != EMPTY_COMMAND)
    {
        return true;
    }
    if (exit_code == EXIT_PROGRAM_SUCCESS || exit_code == FATAL_ERROR)
    {
        return true;
    }
    return false;
}

/*
Parses a line of the file.
It returns SUCCESS if the command execution is successful.
*/
int parse_line(char *line)
{

    strip_newline(line);

    if (strlen(line) == 0)
    {
        return EMPTY_COMMAND;
    }

    string_iterator *iterator = create_string_iterator(line, ' ');

    if (iterator == NULL)
    {
        perror("Initialization iterator problem");
        free(line);
        return FATAL_ERROR;
    }

    if (!has_next_word(iterator))
    {
        destroy_string_iterator(iterator);
        return EMPTY_COMMAND;
    }

    command *command = get_command_from_string_iterator(iterator);

    if (command == NULL)
    {
        perror("Command creation problem");

        free(line);
        destroy_string_iterator(iterator);

        return FATAL_ERROR;
    }

    print_command_in_record_file(command);
    int exit_code = execute_command(command);

    destroy_string_iterator(iterator);
    destroy_command(command);

    return exit_code;
}
