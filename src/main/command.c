#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "constants.h"
#include "command.h"

int debug_command(int args_number, char **args);

command *create_command(char *name, int args_number, char **args)
{
    command *cmd = malloc(sizeof(command));
    assert(cmd != NULL);
    cmd->name = name;
    cmd->args_number = args_number;
    cmd->args = args;
    return cmd;
}
/**
 * Frees the memory allocated for a command.
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

/**
 * Prints a command if verbose mode is enabled.
 */
void print_command(const command *cmd)
{
    if (!verbose)
    {
        return;
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

/**
 * Returns true if the command name matches the given name.
 */
bool is_command(const command *command, const char *name)
{
    return strcmp(command->name, name) == 0;
}

/**
 * Executes a command and returns the exit code.
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
        // pwd command
    }
    else if (is_command(cmd, "mkdir"))
    {
        // mkdir command
    }
    else if (is_command(cmd, "rmdir"))
    {
        // rmdir command
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
        // rm command
    }
    else if (is_command(cmd, "cp"))
    {
        // cp command
    }
    else if (is_command(cmd, "print"))
    {
        // print command
    }
    else if (is_command(cmd, "debug"))
    {
        return debug_command(cmd->args_number, cmd->args);
    }
    else
    {
        // command not found
    }
    return 0;
}

/**
 * Prints the command to the output stream.
 * This is used for debugging purposes.
 */
int debug_command(int args_number, char **args)
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
    return 0;
}