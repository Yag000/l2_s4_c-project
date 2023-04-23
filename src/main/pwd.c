#include <stdlib.h>

#include "pwd.h"
#include "tree_dir_core.h"
#include "string_utils.h"
#include "command.h"
noeud *constant_node;

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

char *get_absolute_path_of_node(noeud *node)
{
    unsigned n = get_number_of_node_in_absolute_path(node);
    char **list_of_absolute_path_name = get_list_of_noeud_above_node(node, n);

    char *absolute_path = concat_words_with_delimiter(n, list_of_absolute_path_name, '/');

    free(list_of_absolute_path_name);

    return absolute_path;
}

char **get_list_of_noeud_above_node(noeud *node, unsigned number_of_parent)
{
    char **list_of_names = malloc(number_of_parent * sizeof(char *));

    unsigned i = 0;
    noeud *temp_noeud = node;

    while (i < number_of_parent)
    {
        list_of_names[number_of_parent - i - 1] = temp_noeud->nom;

        temp_noeud = temp_noeud->pere;
        ++i;
    }
    return list_of_names;
}

unsigned get_number_of_node_in_absolute_path(noeud *node)
{
    if (node == NULL)
    {
        return 0;
    }

    if (are_noeuds_equal(node, node->racine))
    {
        return 1;
    }
    return 1 + get_number_of_node_in_absolute_path(node->pere);
}