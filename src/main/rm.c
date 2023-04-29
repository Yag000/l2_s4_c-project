#include <stdlib.h>
#include <assert.h>

#include "tree_dir_core.h"
#include "command.h"

int rm(const command *cmd)
{
    if (!handle_number_of_args(1, cmd->args_number))
    {
        return 1;
    }
    noeud *node = search_node_in_tree(current_node, cmd->args[0]);

    if (node == NULL)
    {
        write_result_command("Vous avez donné un chemin non valide.");
        return 1;
    }
    if (isNoeudInside(current_node, node))
    {
        write_result_command("Vous ne pouvez pas supprimer un dossier qui est dans le même répertoire que le dossier courant.");
        return 1;
    }
    if (!remove_a_fils_of_noeud(node->pere, node->nom))
    {
        write_result_command("Il y a eu un problème lors de la destruction de l'élément.");
        return 1;
    }
    return 0;
}