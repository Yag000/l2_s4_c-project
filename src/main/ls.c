#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "constants.h"
#include "tree_dir_core.h"

#define FILLER_CHAR ' '
#define START_CONTOUR_CHAR '['
#define END_CONTOUR_CHAR ']'
#define FILE_TYPE_CHAR 'F'
#define DIRECTORY_TYPE_CHAR 'D'

static void print_ls(node *);
static char *get_line_ls(const char *, bool, unsigned);
static void add_transition_at_string(char *, unsigned, unsigned);
static void add_file_type_at_string(char *, unsigned, bool);

int ls(const command *cmd)
{
    if (!handle_number_of_args_with_delimitation(0, 1, cmd->args_number))
    {
        return INVALID_NUMBER_OF_ARGS;
    }

    if (cmd->args_number == 0)
    {
        print_ls(current_node);
        return SUCCESS;
    }

    node *node1 = search_node_in_tree(current_node, cmd->args[0]);

    if (node1 == NULL)
    {
        write_result_command("Invalid path of directory.");
        return INVALID_PATH;
    }
    if (!node1->is_directory)
    {
        write_result_command("Invalid path of directory : the path of a file has been given.");
        return INVALID_SELECTION;
    }

    print_ls(node1);

    return SUCCESS;
}

static void print_ls(node *node)
{
    unsigned max_length_name = get_longest_name_length_of_node_children(node);

    for (liste_node *lst = node->children; lst != NULL; lst = lst->succ)
    {
        char *line = get_line_ls(lst->no->name, lst->no->is_directory, max_length_name);

        write_result_command(line);
        free(line);
    }
}

static char *get_line_ls(const char *name, bool is_directory, unsigned max_length_name)
{
    unsigned len_name = strlen(name);
    unsigned len_transition = max_length_name - len_name + 1;

    char *result = malloc(sizeof(char) * (len_name + len_transition + 4));
    assert(result != NULL);

    memmove(result, name, len_name);

    add_transition_at_string(result, len_name, len_transition);
    add_file_type_at_string(result, len_name + len_transition, is_directory);

    result[len_name + len_transition + 3] = '\0';

    return result;
}

static void add_transition_at_string(char *string_to_fill, unsigned start, unsigned len_transition)
{
    for (unsigned i = start; i < start + len_transition; i++)
    {
        string_to_fill[i] = FILLER_CHAR;
    }
}

static void add_file_type_at_string(char *string_to_fill, unsigned start, bool is_directory)
{
    string_to_fill[start] = START_CONTOUR_CHAR;

    if (is_directory)
    {
        string_to_fill[start + 1] = DIRECTORY_TYPE_CHAR;
    }
    else
    {
        string_to_fill[start + 1] = FILE_TYPE_CHAR;
    }

    string_to_fill[start + 2] = END_CONTOUR_CHAR;
}
