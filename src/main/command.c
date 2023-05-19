#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "constants.h"
#include "string_utils.h"
#include "tree_dir_core.h"

command *create_command(char *name, int args_number, char **args)
{
    command *cmd = malloc(sizeof(command));
    assert(cmd != NULL);
    cmd->name = name;
    cmd->args_number = args_number;
    cmd->args = args;
    return cmd;
}

/*
Frees the memory allocated for a command.
*/
void destroy_command(command *cmd)
{
    free(cmd->name);
    for (int i = 0; i < cmd->args_number; i++)
    {
        free(cmd->args[i]);
    }
    free(cmd->args);
    free(cmd);
}

/*
Prints a command if verbose mode is enabled.
*/
static void print_command(const command *cmd)
{
    if ((out_stream == stdout && interactive) || !verbose)
    {
        return;
    }

    print_command_header();

    fputs(cmd->name, out_stream);
    for (int i = 0; i < cmd->args_number; i++)
    {
        fputs(" ", out_stream);
        fputs(cmd->args[i], out_stream);
    }
    fputs("\n", out_stream);
}

/*
Prints the coimmand header. The command header is the current node path followed by a $.
*/
void print_command_header() { print_command_header_with_stream(out_stream); }

/*
Prints the coimmand header. The command header is the current node path followed by a $.
It will print the header in the given stream.
*/
void print_command_header_with_stream(FILE *stream)
{
    if (current_node != NULL)
    {
        char *path = get_absolute_path_of_node(current_node);
        fputs(path, stream);
        free(path);
    }
    fputs("$ ", stream);
}

int print_command_in_record_file(command *cmd)
{
    if (cmd == NULL || command_record_stream == NULL)
    {
        return EXIT_PROGRAM_SUCCESS;
    }
    fputs(cmd->name, command_record_stream);

    for (int i = 0; i < cmd->args_number; i++)
    {
        fputs(" ", command_record_stream);
        fputs(cmd->args[i], command_record_stream);
    }
    fputs("\n", command_record_stream);

    return SUCCESS;
}

/*
Creates a command from a string iterator.
*/
command *get_command_from_string_iterator(string_iterator *iterator)
{
    if (!has_next_word(iterator))
    {
        perror("Empty iterator problem");
        return NULL;
    }

    char *command_ = next_word(iterator);

    int args_number = get_number_of_words_left(iterator);

    char **args = malloc(sizeof(char *) * args_number);
    assert(args != NULL);

    int i = 0;
    while (has_next_word(iterator))
    {
        args[i] = next_word(iterator);
        i++;
    }

    return create_command(command_, args_number, args);
}

/*
Returns true if the command name matches the given name.
*/
static bool is_command(const command *command, const char *name) { return strcmp(command->name, name) == 0; }

/*
Executes a command and returns the exit code.
*/
int execute_command(const command *cmd)
{
    print_command(cmd);

    if (is_command(cmd, "ls"))
    {
        return ls(cmd);
    }
    if (is_command(cmd, "cd"))
    {
        return cd(cmd);
    }
    if (is_command(cmd, "pwd"))
    {
        return pwd(cmd);
    }
    if (is_command(cmd, "mkdir"))
    {
        return mkdir(cmd);
    }
    if (is_command(cmd, "touch"))
    {
        return touch(cmd);
    }
    if (is_command(cmd, "mv"))
    {
        return mv(cmd);
    }
    if (is_command(cmd, "rm"))
    {
        return rm(cmd);
    }
    if (is_command(cmd, "cp"))
    {
        return cp(cmd);
    }
    if (is_command(cmd, "print"))
    {
        return print(cmd);
    }
    if (is_command(cmd, "echo"))
    {
        return echo(cmd);
    }
    if (is_command(cmd, "exit"))
    {
        return EXIT_PROGRAM_SUCCESS;
    }
    int error_message_size = 100 + strlen(cmd->name);
    char *error_message = malloc(sizeof(char) * (error_message_size + 1));
    snprintf(error_message, error_message_size, "Command not found : %s", cmd->name);
    write_result_command(error_message);
    free(error_message);
    return EXIT_FAILURE;
}

/*
Returns true if the expected number of args is the same of actual
*/
bool handle_number_of_args(unsigned expected, unsigned actual)
{
    if (expected != actual)
    {
        char *error_message = malloc(sizeof(char) * 100);
        snprintf(error_message, 100, "An incorrect number of arguments was given: %u instead of %u expected.", actual,
                 expected);
        write_result_command(error_message);
        free(error_message);
        return false;
    }

    return true;
}

/*
Returns true if the actual number of args is between under_limit and upper_limit
*/
bool handle_number_of_args_with_delimitation(unsigned under_limit, unsigned upper_limit, unsigned actual)
{
    if (actual < under_limit || actual > upper_limit)
    {
        char *error_message = malloc(sizeof(char) * 100);
        snprintf(error_message, 100,
                 "An incorrect number of arguments was given: %u instead of a number between %u and %u expected.",
                 actual, under_limit, upper_limit);
        write_result_command(error_message);
        free(error_message);
        return false;
    }

    return true;
}

/*
Writes the string of result in the out_stream
*/
int write_result_command(char *result)
{
    // We need to also write the result in stdout if we are in interactive mode.
    // If not the user will not see the result.
    if (interactive && out_stream != stdout)
    {
        fputs(result, stdout);
        fputs("\n", stdout);
    }

    fputs(result, out_stream);
    fputs("\n", out_stream);

    return SUCCESS;
}

/*
Writes writes a series of strings in the out_stream
*/
int write_result_lines_command(size_t lines_number, char **results)
{
    for (unsigned i = 0; i < lines_number; i++)
    {
        write_result_command(results[i]);
    }
    return SUCCESS;
}
