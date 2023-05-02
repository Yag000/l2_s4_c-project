
#include <assert.h>

#include "command.h"
#include "constants.h"
#include "string_utils.h"
#include "tree_dir_core.h"

/*
Creates a file with the given name. The name is the last
word of the path.
*/
int touch(const command *cmd)
{
    if (!handle_number_of_args(1, cmd->args_number))
    {
        return INVALID_NUMBER_OF_ARGS;
    }

   noeud *new_node = search_node_in_tree_with_node_creation(current_node, cmd->args[0], false);

    if (new_node == NULL)
    {
        write_result_command("Invalid path of file.");
        return INVALID_NAME;
    }

    if (!append_a_fils_to_noeud(new_node->pere, new_node))
    {
        write_result_command("Error while creating file.");
        destroy_noeud(new_node);
        return FATAL_ERROR;
    }

    return SUCCESS;
}
