#include <assert.h>
#include <stdlib.h>

#include "command.h"
#include "constants.h"
#include "tree_dir_core.h"

int mv(const command *cmd)
{
    if (!handle_number_of_args(2, cmd->args_number))
    {
        return INVALID_NUMBER_OF_ARGS;
    }
    node *node_to_move = search_node_in_tree(current_node, cmd->args[0]);

    if (node_to_move == NULL)
    {
        write_result_command("Invalid path to move.");
        return INVALID_PATH;
    }

    if (is_node_inside(current_node, node_to_move))
    {
        write_result_command("An directory containing the current node cannot be moved.");
        return INVALID_SELECTION;
    }

    node *node_to_append =
        search_node_in_tree_with_node_creation(current_node, cmd->args[1], node_to_move->is_directory);

    if (node_to_append == NULL)
    {
        write_result_command("Invalid path for the movement.");
        return INVALID_PATH;
    }

    if (!is_valid_name_node(node_to_append->nom))
    {
        write_result_command(
            "Invalid name : the name of an element can neither be empty nor contain special characters.");
        destroy_node(node_to_append);
        return INVALID_NAME;
    }

    if (is_node_inside(node_to_append->parent, node_to_move))
    {
        write_result_command("A directory cannot be moved inside itself.");
        destroy_node(node_to_append);
        return INVALID_SELECTION;
    }

    int append_error_value = append_child_to_node(node_to_append->parent, node_to_append);

    if (append_error_value == INVALID_NAME)
    {
        write_result_command("Invalid name : an element with the same name already exists.");
        destroy_node(node_to_append);
        return INVALID_NAME;
    }

    if (append_error_value != SUCCESS)
    {
        write_result_command("Error while moving the element.");
        destroy_node(node_to_append);
        return FATAL_ERROR;
    }

    int remove_error_value = remove_a_child_from_children(node_to_move->parent, node_to_move);

    if (remove_error_value != SUCCESS)
    {
        write_result_command("Error while moving the element.");
        return FATAL_ERROR;
    }

    move_children_of_node_to_new_node(node_to_move, node_to_append);

    return SUCCESS;
}
