#include <stdlib.h>

#include "command.h"
#include "constants.h"
#include "tree_dir_core.h"

int cd(const command *cmd)
{
    if (!handle_number_of_args_with_delimitation(0, 1, cmd->args_number))
    {
        return INVALID_NUMBER_OF_ARGS;
    }


    if (cmd->args_number == 0)
    {
        current_node = current_node->racine;
        write_result_command("");
        return SUCCESS;
    }

    noeud *tmp = search_node_in_tree(current_node, cmd->args[0]);

    if (tmp == NULL || !tmp-> est_dossier)
    {
        // TODO: improve this error message
        write_result_command("Invalid path.");
        return INVALID_PATH;
    }

    current_node = tmp;
    write_result_command("");
    return SUCCESS;
}
