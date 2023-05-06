#ifndef COMMAND_H
#define COMMAND_H

#include "string_utils.h"
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
command *get_command_from_string_iterator(string_iterator *);

int execute_command(const command *);
void print_command_header_with_stream(FILE *);
void print_command_header();

bool handle_number_of_args(unsigned, unsigned);
bool handle_number_of_args_with_delimitation(unsigned, unsigned, unsigned);
int write_result_command(char *);
int write_result_lines_command(size_t, char **);
int print_command_in_record_file(command *);

int pwd(const command *);
int rm(const command *);
int ls(const command *);
int print(const command *);
int mkdir(const command *);
int touch(const command *);
int cp(const command *);
int cd(const command *);
int mv(const command *);
int echo(const command *);

#endif
