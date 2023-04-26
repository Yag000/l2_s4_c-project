#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "tree_dir_core.h"
#include "command.h"

static void print_ls(noeud *noeud);
static char *get_line_ls(const char *nom, bool est_dossier);

int ls(const command *cmd)
{
    if (!handle_number_of_args_with_delimitation(0, 1, cmd->args_number))
    {
        return 1;
    }
    if (cmd->args_number == 0)
    {
        print_ls(current_node);
    }
    else
    {
        noeud *node = search_node_in_tree(current_node, cmd->args[0]);

        if (node == NULL)
        {
            write_result_command("Vous avez donné un chemin non valide.");
            return 1;
        }
        if (!node->est_dossier)
        {
            write_result_command("La commande ls n'est pas appliquable à ce fichier : ce n'est pas un dossier.");
            return 1;
        }

        print_ls(node);
    }

    return 0;
}

static void print_ls(noeud *noeud)
{
    for (liste_noeud *lst = noeud->fils; lst != NULL; lst = lst->succ)
    {
        char *line = get_line_ls(lst->no->nom, lst->no->est_dossier);

        write_result_command(line);
        free(line);
    }
}

static char *get_line_ls(const char *nom, bool est_dossier)
{
    unsigned len_nom = strlen(nom);

    char *result = malloc(sizeof(char) * (len_nom + 5));
    memmove(result, nom, len_nom);

    result[len_nom] = ' ';
    result[len_nom + 1] = '(';

    if (est_dossier)
    {
        result[len_nom + 2] = 'D';
    }
    else
    {
        result[len_nom + 2] = 'F';
    }

    result[len_nom + 3] = ')';
    result[len_nom + 4] = '\0';

    return result;
}