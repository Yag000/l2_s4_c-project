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
    char *start_with_name;

    if (depth == 0)
    {
        start_with_name = get_alloc_pointer_of_string("/");
    }
    else
    {
        char *space_start = repeat_char(' ', depth * 4 - 1);

        start_with_name = concat_two_words_with_delimiter(space_start, nom, ' ');

        free(space_start);
    }

    if (start_with_name == NULL)
    {
        return NULL;
    }

    char *type_of_file;

    if (est_dossier)
    {
        type_of_file = "(D)";
    }
    else
    {
        type_of_file = "(F)";
    }

    char *result = concat_two_words_with_delimiter(start_with_name, type_of_file, ' ');
    free(start_with_name);

    return result;
}