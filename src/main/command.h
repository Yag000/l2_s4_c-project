#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct command
{
    char *name;
    int args_number;
    char **args;

} command;

command *create_command(char *name, int args_number, char **args);
void destroy_command(command *cmd);

int execute_command(const command *cmd);

bool handle_number_of_args(unsigned expected, unsigned actual);
int write_result_command(char *result);
int write_result_lines_command(size_t line_number, char **results);

int pwd(const command *cmd);
int mkdir(const command *);

#endif