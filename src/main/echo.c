#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "constants.h"
#include "string_utils.h"

/*
Prints the command to the output stream.
*/
int echo(const command *cmd)
{
    char *result = concat_words_with_delimiter(cmd->args_number, cmd->args, ' ');
    if (strcmp(result, "") != 0)
    {
        write_result_command(result);
    }
    free(result);

    return SUCCESS;
}
