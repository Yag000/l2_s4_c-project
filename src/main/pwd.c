#include <stdlib.h>
#include <assert.h>

#include "tree_dir_core.h"
#include "string_utils.h"
#include "command.h"

/**
 * Adds to the output the absolute path of the constant node
 */
int pwd(const command *cmd)
{
    if (!handle_number_of_args(0, cmd->args_number))
    {
        return 1;
    }

    char *path = get_absolute_path_of_node(current_node);
    int error_value = write_result_command(path);

    free(path);

    return error_value;
}

/**
 * Returns the string containing the absolute path of the node
 */
char *get_absolute_path_of_node(const noeud *node)
{
    assert(node != NULL);

    char *absolute_path;

    if (is_root_node(node))
    {
        absolute_path = malloc(2 * sizeof(char));
        absolute_path[0] = '/';
        absolute_path[1] = '\0';

        return absolute_path;
    }

    if (is_root_node(node->pere))
    {
        char *root_path = malloc(sizeof(char));
        root_path[0] = '\0';

        absolute_path = concat_two_words_with_delimiter(root_path, node->nom, '/');

        free(root_path);

        return absolute_path;
    }

    char *parent_absolute_path = get_absolute_path_of_node(node->pere);
    absolute_path = concat_two_words_with_delimiter(parent_absolute_path, node->nom, '/');

    free(parent_absolute_path);

    return absolute_path;
}
