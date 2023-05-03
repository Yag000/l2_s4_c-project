#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "parser.h"
#include "tree_dir_core.h"

FILE *out_stream;

bool verbose = false;
noeud *current_node;
bool interactive;

typedef struct flags
{
    bool verbose;
    bool interactive;
} flags;

static flags *parse_flags(int, char *[]);

int main(int argc, char *argv[])
{
    out_stream = stdout;

    flags *flag = parse_flags(argc, argv);
    verbose = flag->verbose;
    interactive = flag->interactive;
    free(flag);

    current_node = create_root_noeud();

    int error_code = parse_file(argv[1]);

    destroy_tree();

    return error_code == SUCCESS || error_code == EXIT_PROGRAM_SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE;
}

static flags *parse_flags(int argc, char *argv[])
{
    flags *flag = malloc(sizeof(flags));
    flag->verbose = false;
    flag->interactive = false;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-v") == 0)
        {
            flag->verbose = true;
        }
        else if (strcmp(argv[i], "-i") == 0)
        {
            flag->interactive = true;
        }
    }
    return flag;
}
