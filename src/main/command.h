#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>

typedef struct command
{
    char *name;
    int args_number;
    char **args;

} command;

command *create_command(char *, int, char **);
void destroy_command(command *);

int execute_command(const command *);

bool handle_number_of_args(unsigned, unsigned);
int write_result_command(char *);
int write_result_lines_command(size_t, char **);

int pwd(const command *);
int rm(const command *cmd);

#endif