#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "constants.h"
#include "tree_dir_core.h"

static int debug_command(int, char **);

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
    if (!verbose)
    {
        return;
    }

    if (current_node != NULL)
    {
        char *path = get_absolute_path_of_node(current_node);
        fputs(path, out_stream);
        free(path);
    }

    fputs("$ ", out_stream);

    fputs(cmd->name, out_stream);
    for (int i = 0; i < cmd->args_number; i++)
    {
        fputs(" ", out_stream);
        fputs(cmd->args[i], out_stream);
    }
    fputs("\n", out_stream);
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
    // TODO we need to implement the commands and their return value
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
        // mv command
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
    if (is_command(cmd, "debug"))
    {
        return debug_command(cmd->args_number, cmd->args);
    }
    write_result_command("Command not found");
    write_result_command(cmd->name);
    return EXIT_FAILURE;
}

/*
Prints the command to the output stream.
This is used for debugging purposes.
*/
static int debug_command(int args_number, char **args)
{
    for (int i = 0; i < args_number; i++)
    {
        fputs(args[i], out_stream);
        if (i < args_number - 1)
        {
            fputs(" ", out_stream);
        }
    }
    fputs("\n", out_stream);
    return SUCCESS;
}

/*
Returns true if the expected number of args is the same of actual
*/
bool handle_number_of_args(unsigned expected, unsigned actual)
{
    if (expected != actual)
    {
        fprintf(out_stream, "An incorrect number of arguments was given: %u instead of %u expected.\n", actual,
                expected);
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
        fprintf(out_stream,
                "An incorrect number of arguments was given: %u instead of a number between %u and %u expected.\n",
                actual, under_limit, upper_limit);
        return false;
    }

    return true;
}

/*
Writes the string of result in the out_stream
*/
int write_result_command(char *result)
{
    fputs(result, out_stream);
    fputs("\n", out_stream);

    return SUCCESS;
}

/*
Writes all string of results in the out_stream
*/
int write_result_lines_command(size_t lines_number, char **results)
{
    for (unsigned i = 0; i < lines_number; i++)
    {
        write_result_command(results[i]);
    }
    return SUCCESS;
}
