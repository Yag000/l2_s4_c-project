#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "constants.h"
#include "command.h"
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
static bool is_command(const command *command, const char *name)
{
    return strcmp(command->name, name) == 0;
}

/*
Executes a command and returns the exit code.
*/
int execute_command(const command *cmd)
{
    // TODO we need to implement the commands and their return value
    print_command(cmd);
    if (is_command(cmd, "ls"))
    {
        // ls command
    }
    else if (is_command(cmd, "cd"))
    {
        // cd command
    }
    else if (is_command(cmd, "pwd"))
    {
        return pwd(cmd);
    }
    else if (is_command(cmd, "mkdir"))
    {
        // mkdir command
    }
    else if (is_command(cmd, "touch"))
    {
        // touch command
    }
    else if (is_command(cmd, "cat"))
    {
        // cat command
    }
    else if (is_command(cmd, "mv"))
    {
        // mv command
    }
    else if (is_command(cmd, "rm"))
    {
        return rm(cmd);
    }
    else if (is_command(cmd, "cp"))
    {
        // cp command
    }
    else if (is_command(cmd, "print"))
    {
        return print(cmd);
    }
    else if (is_command(cmd, "debug"))
    {
        return debug_command(cmd->args_number, cmd->args);
    }
    else
    {
        // command not found
    }
    return SUCCESS;
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
        fprintf(out_stream,
                "An incorrect number of arguments was given: %u instead of %u expected.\n",
                actual,
                expected);
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
    for (int i = 0; i < lines_number; i++)
    {
        write_result_command(results[i]);
    }
    return SUCCESS;
}
