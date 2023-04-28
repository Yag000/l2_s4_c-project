#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "tree_dir_core.h"
#include "command.h"

#define FILLER_CHAR ' '
#define START_CONTOUR_CHAR '['
#define END_CONTOUR_CHAR ']'
#define FILE_TYPE_CHAR 'F'
#define DIRECTORY_TYPE_CHAR 'D'

static void print_ls(noeud *);
static char *get_line_ls(const char *, bool, unsigned);
static void add_transition_at_string(char *, unsigned, unsigned);
static void add_file_type_at_string(char *, unsigned, bool);

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
    unsigned max_length_name = get_max_number_of_char_of_node_fils_name(noeud);

    for (liste_noeud *lst = noeud->fils; lst != NULL; lst = lst->succ)
    {
        char *line = get_line_ls(lst->no->nom, lst->no->est_dossier, max_length_name);

        write_result_command(line);
        free(line);
    }
}

static char *get_line_ls(const char *nom, bool est_dossier, unsigned max_length_name)
{
    unsigned len_name = strlen(nom);
    unsigned len_transition = max_length_name - len_name + 1;

    char *result = malloc(sizeof(char) * (len_name + len_transition + 4));
    assert(result != NULL);

    memmove(result, nom, len_name);

    add_transition_at_string(result, len_name, len_transition);
    add_file_type_at_string(result, len_name + len_transition, est_dossier);

    result[len_name + len_transition + 3] = '\0';

    return result;
}

static void add_transition_at_string(char *string_to_fill, unsigned start, unsigned len_transition)
{
    for (unsigned i = start; i < start + len_transition; i++)
    {
        string_to_fill[i] = FILLER_CHAR;
    }
}

static void add_file_type_at_string(char *string_to_fill, unsigned start, bool est_dossier)
{
    string_to_fill[start] = START_CONTOUR_CHAR;

    if (est_dossier)
    {
        string_to_fill[start + 1] = DIRECTORY_TYPE_CHAR;
    }
    else
    {
        string_to_fill[start + 1] = FILE_TYPE_CHAR;
    }

    string_to_fill[start + 2] = END_CONTOUR_CHAR;
}