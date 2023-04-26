#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "string_utils.h"
#include "command.h"
#include "tree_dir_core.h"

static char *get_a_print_line(const char *nom, bool est_dossier, unsigned depth);
static void print_with_depth(noeud *node, unsigned depth);

int print(const command *cmd)
{
    if (!handle_number_of_args(0, cmd->args_number))
    {
        return 1;
    }
    print_with_depth(current_node->racine, 0);

    return 0;
}

static void print_with_depth(noeud *node, unsigned depth)
{
    char *line = get_a_print_line(node->nom, node->est_dossier, depth);
    write_result_command(line);

    free(line);

    if (!node->est_dossier)
    {
        return;
    }
    for (liste_noeud *lst = node->fils; lst != NULL; lst = lst->succ)
    {
        print_with_depth(lst->no, depth + 1);
    }
}

static char *get_a_print_line(const char *nom, bool est_dossier, unsigned depth)
{
    unsigned n_start_space = depth * 4;
    unsigned n_name = strlen(nom);

    if (n_name == 0)
    {
        n_name += 1;
    }

    char *result = malloc(sizeof(char) * (n_start_space + n_name + 5));

    for (unsigned i = 0; i < n_start_space; i++)
    {
        result[i] = ' ';
    }

    if (strcmp(nom, "") == 0)
    {
        result[n_start_space] = '/';
    }
    else
    {
        memmove(result + n_start_space, nom, n_name);
    }

    result[n_start_space + n_name] = ' ';
    result[n_start_space + n_name + 1] = '(';

    if (est_dossier)
    {
        result[n_start_space + n_name + 2] = 'D';
    }
    else
    {
        result[n_start_space + n_name + 2] = 'F';
    }

    result[n_start_space + n_name + 3] = ')';
    result[n_start_space + n_name + 4] = '\0';

    return result;
}