#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "constants.h"
#include "command.h"

int debug_command(int argsNumber, char **args);

command *create_command(char *name, int argsNumber, char **args)
{
    command *cmd = malloc(sizeof(command));
    cmd->name = name;
    cmd->argsNumber = argsNumber;
    cmd->args = args;
    return cmd;
}

void destroy_command(command *cmd)
{
    free(cmd->name);
    for (int i = 0; i < cmd->argsNumber; i++)
    {
        free(cmd->args[i]);
    }
    free(cmd->args);
    free(cmd);
}

void print_command(const command *cmd)
{
    if (!verbose)
    {
        return;
    }

    printf("$ %s ", cmd->name);
    for (int i = 0; i < cmd->argsNumber; i++)
    {
        printf("%s ", cmd->args[i]);
    }
    puts("");
}

bool is_command(const command *command, const char *name)
{
    return strcmp(command->name, name) == 0;
}

int parse_command(const command *cmd)
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
        return debug_command(cmd->argsNumber, cmd->args);
    }
    else
    {
        // command not found
    }
    return 0;
}

int debug_command(int argsNumber, char **args)
{
    for (int i = 0; i < argsNumber; i++)
    {
        if (verbose && out_stream != stdout)
        {
            printf("%s ", args[i]);
        }
        fputs(args[i], out_stream);
        if (i < argsNumber - 1)
        {
            fputs(" ", out_stream);
        }
    }
    if (verbose && out_stream != stdout)
    {
        printf("\n");
    }
    fputs("\n", out_stream);
    return 0;
}