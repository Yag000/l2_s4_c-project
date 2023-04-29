#include <stdlib.h>
#include <assert.h>

#include "tree_dir_core.h"
#include "command.h"
#include "constants.h"

/*
Adds to the output the absolute path of the current node.
*/
int pwd(const command *cmd)
{
    if (!handle_number_of_args(0, cmd->args_number))
    {
        return INVALID_NUMBER_OF_ARGS;
    }

    char *path = get_absolute_path_of_node(current_node);
    write_result_command(path);

    free(path);

    return SUCCESS;
}
