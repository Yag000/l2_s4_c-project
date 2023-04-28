#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "string_utils.h"
#include "tree_dir_core.h"

#define FILLER_SIZE 4
#define ROOT_CHAR '/'
#define FILLER_CHAR ' '
#define UNION_CHAR '-'
#define BORDER_CHAR '|'
#define TRANSITION_CHAR '\\'
#define START_CONTOUR_CHAR '('
#define END_CONTOUR_CHAR ')'
#define FILE_TYPE_CHAR 'F'
#define DIRECTORY_TYPE_CHAR 'D'

static void print_with_depth(noeud *, unsigned, bool);
static char *get_a_print_line(const char *, bool, unsigned, bool);
static void add_start_transition_at_string(char *, unsigned, bool);
static void add_file_name_at_string(char *, const char *, unsigned, unsigned);
static void add_file_type_at_string(char *, unsigned, bool);

static char *last_line = NULL;

int print(const command *cmd)
{
    if (!handle_number_of_args(0, cmd->args_number))
    {
        return 1;
    }
    print_with_depth(current_node->racine, 0, false);

    free(last_line);
    last_line = NULL;
    return 0;
}

static void print_with_depth(noeud *node, unsigned depth, bool is_last)
{
    char *line = get_a_print_line(node->nom, node->est_dossier, depth, is_last);

    write_result_command(line);
    if (last_line != NULL)
    {
        free(last_line);
    }
    last_line = line;

    if (!node->est_dossier)
    {
        return;
    }
    for (liste_noeud *lst = node->fils; lst != NULL; lst = lst->succ)
    {
        if (lst->succ == NULL)
        {

            print_with_depth(lst->no, depth + 1, true);
        }
        else
        {
            print_with_depth(lst->no, depth + 1, false);
        }
    }
}

static char *get_a_print_line(const char *nom, bool est_dossier, unsigned depth, bool is_last)
{
    unsigned len_start_transition = depth * FILLER_SIZE;
    unsigned len_name = strlen(nom);

    if (len_name == 0)
    {
        len_name += 1;
    }

    char *result = malloc(sizeof(char) * (len_start_transition + len_name + 5));

    add_start_transition_at_string(result, len_start_transition, is_last);
    add_file_name_at_string(result, nom, len_start_transition, len_name);

    result[len_start_transition + len_name] = FILLER_CHAR;

    add_file_type_at_string(result, len_start_transition + len_name + 1, est_dossier);

    result[len_start_transition + len_name + 4] = '\0';

    return result;
}

static void add_start_transition_at_string(char *string_to_fill, unsigned end, bool is_last)
{
    if (end == 0)
    {
        return;
    }

    unsigned last_line_len;

    if (last_line == NULL)
    {
        last_line_len = 0;
    }
    else
    {
        last_line_len = strlen(last_line);
    }

    for (unsigned i = 0; i < end - 1; i++)
    {
        if (i % FILLER_SIZE == 0)
        {
            if (is_last && end - i <= FILLER_SIZE)
            {
                string_to_fill[i] = TRANSITION_CHAR;
            }
            else if (i <= last_line_len && (last_line[i] == '\\' || last_line[i] == ' '))
            {
                string_to_fill[i] = FILLER_CHAR;
            }
            else
            {
                string_to_fill[i] = BORDER_CHAR;
            }
        }

        else if (end - i < FILLER_SIZE)
        {
            string_to_fill[i] = UNION_CHAR;
        }
        else
        {
            string_to_fill[i] = FILLER_CHAR;
        }
    }

    string_to_fill[end - 1] = FILLER_CHAR;
}

static void add_file_name_at_string(char *string_to_fill, const char *nom, unsigned start, unsigned len_name)
{
    if (strcmp(nom, "") == 0)
    {
        string_to_fill[start] = ROOT_CHAR;
    }
    else
    {
        memmove(string_to_fill + start, nom, len_name);
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