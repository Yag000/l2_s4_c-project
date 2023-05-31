#include <assert.h>
#include <stdlib.h>

#include "command.h"
#include "constants.h"
#include "tree_dir_core.h"

int rm(const command *cmd)
{
    if (!handle_number_of_args(1, cmd->args_number))
    {
        return INVALID_NUMBER_OF_ARGS;
    }
    noeud *node1 = search_node_in_tree(current_node, cmd->args[0]);

    if (node1 == NULL)
    {
        write_result_command("Invalid path given.");
        return INVALID_PATH;
    }
    if (is_noeud_inside(current_node, node1))
    {
        write_result_command("A directory that contains the current folder cannot be deleted.");
        return INVALID_SELECTION;
    }

    int remove_error_value = remove_a_fils_of_noeud(node1->pere, node1->nom);

    if (remove_error_value != SUCCESS)
    {
        write_result_command("There was a problem during the destruction of the element.");
        return FATAL_ERROR;
    }
    return SUCCESS;
}