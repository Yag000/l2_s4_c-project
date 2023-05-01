#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "tree_dir_core.h"
#include "command.h"
#include "constants.h"

static void copy_content_of(noeud *, noeud *);

int cp(const command *cmd)
{
    if (!handle_number_of_args(2, cmd->args_number))
    {
        return INVALID_NUMBER_OF_ARGS;
    }
    noeud *node_to_copy = search_node_in_tree(current_node, cmd->args[0]);

    if (node_to_copy == NULL)
    {
        write_result_command("Invalid path to copy.");
        return INVALID_PATH;
    }

    noeud *node_to_append = search_node_in_tree_with_node_creation(current_node, cmd->args[1], node_to_copy->est_dossier);

    if (node_to_append == NULL)
    {
        write_result_command("Invalid path to create a copy.");
        return INVALID_PATH;
    }

    if (is_noeud_inside(node_to_append->pere, node_to_copy))
    {
        write_result_command("An element cannot be copied inside a directory contained in the copy.");
        destroy_noeud(node_to_append);
        return INVALID_SELECTION;
    }

    if (!append_a_fils_to_noeud(node_to_append->pere, node_to_append))
    {
        write_result_command("Error while creating directory.");
        destroy_noeud(node_to_append);
        return FATAL_ERROR;
    }

    copy_content_of(node_to_append, node_to_copy);

    return SUCCESS;
}

/*
Copy all contents of node1 inside node2

The node1 should be empty to avoid problem of same name in append
*/
static void copy_content_of(noeud *node1, noeud *node2)
{
    if (!node1->est_dossier || !node2->est_dossier)
    {
        return;
    }
    for (liste_noeud *lst = node2->fils; lst != NULL; lst = lst->succ)
    {
        noeud *node_to_append = create_noeud(lst->no->est_dossier, lst->no->nom, node1);
        append_a_fils_to_noeud(node1, node_to_append);

        copy_content_of(node_to_append, lst->no);
    }
}