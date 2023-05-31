#include <assert.h>

#include "command.h"
#include "constants.h"
#include "string_utils.h"
#include "tree_dir_core.h"

/*
Creates a directory with the given name. The name is the last
word of the path.
*/
int mkdir(const command *cmd)
{
    if (!handle_number_of_args(1, cmd->args_number))
    {
        return INVALID_NUMBER_OF_ARGS;
    }

    node *new_node = search_node_in_tree_with_node_creation(current_node, cmd->args[0], true);

    if (new_node == NULL)
    {
        write_result_command("Invalid path of directory.");
        return INVALID_PATH;
    }
    if (!is_valid_name_node(new_node->nom))
    {
        write_result_command(
            "Invalid name : the name of an element can neither be empty nor contain special characters.");
        destroy_node(new_node);
        return INVALID_NAME;
    }

    int append_error_value = append_child_to_node(new_node->parent, new_node);

    if (append_error_value == INVALID_NAME)
    {
        write_result_command("Invalid name : an element with the same name already exists.");
        destroy_node(new_node);
        return INVALID_NAME;
    }

    if (append_error_value != SUCCESS)
    {
        write_result_command("Error while creating directory.");
        destroy_node(new_node);
        return FATAL_ERROR;
    }

    return SUCCESS;
}
