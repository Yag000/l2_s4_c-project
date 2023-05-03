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

    noeud *new_node = search_node_in_tree_with_node_creation(current_node, cmd->args[0], true);

    if (new_node == NULL)
    {
        write_result_command("Invalid path of directory.");
        return INVALID_NAME;
    }

    int append_error_value = append_a_fils_to_noeud(new_node->pere, new_node);

    if (append_error_value == INVALID_NAME)
    {
        write_result_command("Invalid name : an element with the same name already exists.");
        destroy_noeud(new_node);
    }

    return append_error_value;
}
