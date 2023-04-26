#include <assert.h>

#include "tree_dir_core.h"
#include "command.h"
#include "constants.h"
#include "string_utils.h"

/*
Creates a directory with the given name. For now it only handles
the case where the directory is created in the current directory.
*/
int mkdir(const command *cmd)
{
    if (!handle_number_of_args(1, cmd->args_number))
    {
        return INVALID_NUMBER_OF_ARGS;
    }

    noeud *new_node = get_new_node_from_path(current_node, cmd-> args[0], true);

    if (new_node == NULL){
        write_result_command("Invalid name for directory");
        return  INVALID_NAME;
    }

    if (!append_a_fils_to_noeud(current_node, new_node))
    {
        write_result_command("Error while creating directory");
        destroy_noeud(new_node);
        return FATAL_ERROR;
    }

    return SUCCESS;
}
