#include <stdlib.h>
#include <assert.h>

#include "tree_dir_core.h"
#include "command.h"
#include "constants.h"

int mv(const command *cmd)
{
    if (!handle_number_of_args(2, cmd->args_number))
    {
        return INVALID_NUMBER_OF_ARGS;
    }
    noeud *node_to_move = search_node_in_tree(current_node, cmd->args[0]);

    if (node_to_move == NULL)
    {
        write_result_command("Invalid path to move.");
        return INVALID_PATH;
    }

    if (is_noeud_inside(current_node, node_to_move))
    {
        write_result_command("An directory containing the current node cannot be moved.");
        return INVALID_SELECTION;
    }

    noeud *node_to_append = search_node_in_tree_with_node_creation(current_node, cmd->args[1], node_to_move->est_dossier);

    if (node_to_append == NULL)
    {
        write_result_command("Invalid path for the movement.");
        return INVALID_PATH;
    }

    if (!is_valid_name_node(node_to_append->nom))
    {
        write_result_command("Invalid name : the name of an element can neither be empty nor contain special characters.");
        destroy_noeud(node_to_append);
        return INVALID_NAME;
    }

    if (is_noeud_inside(node_to_append->pere, node_to_move))
    {
        write_result_command("A directory cannot be moved inside itself.");
        destroy_noeud(node_to_append);
        return INVALID_SELECTION;
    }

    int append_error_value = append_a_fils_to_noeud(node_to_append->pere, node_to_append);

    if (append_error_value == INVALID_NAME)
    {
        write_result_command("Invalid name : an element with the same name already exists.");
        destroy_noeud(node_to_append);
        return INVALID_NAME;
    }

    if (append_error_value != SUCCESS)
    {
        write_result_command("Error while moving the element.");
        destroy_noeud(node_to_append);
        return FATAL_ERROR;
    }

    int remove_error_value = remove_a_node_from_fils(node_to_move->pere, node_to_move);

    if (remove_error_value != SUCCESS)
    {
        write_result_command("Error while moving the element.");
        return FATAL_ERROR;
    }

    move_fils_of_node_to_new_node(node_to_move, node_to_append);

    return SUCCESS;
}