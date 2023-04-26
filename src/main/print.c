#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "string_utils.h"
#include "command.h"

int print(const command *cmd)
{
    if (!handle_number_of_args(0, cmd->args_number))
    {
        return 1;
    }
}

char *get_a_print_line(const char *nom, bool est_dossier, unsigned p)
{
    char *space_start = repeat_char(' ', p * 4 - 1);

    if (space_start == NULL)
    {
        return NULL;
    }
    char *start_with_name = concat_two_words_with_delimiter(space_start, nom, ' ');
    free(space_start);

    if (start_with_name == NULL)
    {
        return NULL;
    }
    char *type_of_file;

    if (est_dossier)
    {
    }
}