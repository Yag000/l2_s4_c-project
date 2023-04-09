#ifndef COMMAND_H
#define COMMAND_H

typedef struct command
{
    char *name;
    int args_number;
    char **args;

} command;

command *create_command(char *name, int args_number, char **args);
void destroy_command(command *cmd);

int execute_command(const command *cmd);

#endif