#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct command
{
    char *name;
    int args_number;
    char **args;

} command;

command *create_command(char *, int, char **);
void destroy_command(command *);

int execute_command(const command *);
void print_command_header_with_stream(FILE *);
void print_command_header();

bool handle_number_of_args(unsigned, unsigned);
bool handle_number_of_args_with_delimitation(unsigned, unsigned, unsigned);
int write_result_command(char *);
int write_result_lines_command(size_t, char **);

int pwd(const command *);
int rm(const command *);
int ls(const command *);
int print(const command *);
int mkdir(const command *);
int touch(const command *);
int cp(const command *);
int cd(const command *);
int mv(const command *);

#endif
