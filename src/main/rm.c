#include <stdlib.h>
#include <assert.h>

#include "tree_dir_core.h"
#include "command.h"
#include "constants.h"

int rm(const command *cmd)
{
    if (!handle_number_of_args(1, cmd->args_number))
    {
        return INVALID_NUMBER_OF_ARGS;
    }
    noeud *node = search_node_in_tree(current_node, cmd->args[0]);

    if (node == NULL)
    {
        write_result_command("Invalid path given.");
        return INVALID_PATH;
    }
    if (is_noeud_inside(current_node, node))
    {
        write_result_command("A directory that contains the current folder cannot be deleted.");
        return INVALID_SELECTION;
    }
    if (!remove_a_fils_of_noeud(node->pere, node->nom))
    {
        write_result_command("There was a problem during the destruction of the element.");
        return FATAL_ERROR;
    }
    return 0;
}