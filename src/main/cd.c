#include <stdlib.h>

#include "command.h"
#include "tree_dir_core.h"

int cd(command *cmd)
{
    // TODO handle to many arguments


    if (cmd->args_number == 0)
    {
        current_node = current_node->racine;
        // TODO: update this with the appropriate constant from PR 55
        return 0;
    }

    noeud *tmp = search_node_in_tree(current_node, cmd->args[0]);

    if (tmp == NULL)
    {
        // TODO: improve this error message
        write_result_command("Chemin non valide.");
        // TODO: update this with the appropriate constant from PR 55
        return 1;
    }

    current_node = tmp;
    // TODO: update this with the appropriate constant from PR 55
    return 0;
}
