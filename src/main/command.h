#ifndef COMMAND_H
#define COMMAND_H

typedef struct command
{
    char *name;
    int argsNumber;
    char **args;

} command;

command *create_command(char *name, int argsNumber, char **args);
void destroy_command(command *cmd);

int parse_command(const command *cmd);

#endif