#include <stdlib.h>
#include <assert.h>

#include "tree_dir_core.h"
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
