#include <stdlib.h>

#include "pwd.h"
#include "tree_dir_core.h"
#include "string_utils.h"
#include "command.h"
noeud *constant_node;

/**
 * Adds to the output the absolute path of the constant node
 */
int pwd(const command *cmd)
{
    if (!handle_number_of_args(0, cmd->args_number))
    {
        return 1;
    }

    char *path = get_absolute_path_of_node(constant_node);
    int error_value = write_result_command(path);

    free(path);

    return error_value;
}

/**
 * Returns the string containing the absolute path of the node
 */
char *get_absolute_path_of_node(noeud *node)
{
    unsigned n = get_number_of_node_in_absolute_path(node);
    char **list_of_absolute_path_name = get_list_of_noeud_above_node(node, n);

    char *absolute_path = concat_words_with_delimiter(n, list_of_absolute_path_name, '/');

    free(list_of_absolute_path_name);

    return absolute_path;
}

/**
 * Returns the list of n - 1 names of the node's parents, with the given node as the nth node
 */
char **get_list_of_noeud_above_node(noeud *node, unsigned n)
{
    char **list_of_names = malloc(n * sizeof(char *));

    unsigned i = 0;
    noeud *temp_noeud = node;

    while (i < n)
    {
        list_of_names[n - i - 1] = temp_noeud->nom;

        temp_noeud = temp_noeud->pere;
        ++i;
    }
    return list_of_names;
}

/**
 * Returns the number of parents above the node, with the given node included
 */
unsigned get_number_of_node_in_absolute_path(noeud *node)
{
    if (node == NULL)
    {
        return 0;
    }

    if (is_root_node(node))
    {
        return 1;
    }
    return 1 + get_number_of_node_in_absolute_path(node->pere);
}