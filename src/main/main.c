#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "parser.h"
#include "tree_dir_core.h"

FILE *out_stream;

bool verbose = false;
noeud *current_node;

typedef struct flags
{
    bool verbose;
    bool interactive;
    bool error_occurs_stop;
} flags;

static flags *parse_flags(int, char *[]);
static void activate_flags(flags *);

int main(int argc, char *argv[])
{
    out_stream = stdout;

    // Hnadle 0 arguments
    if (argc <= 1)
    {
        perror("No argument was given");
        return EXIT_FAILURE;
    }

    flags *flag = parse_flags(argc, argv);
    activate_flags(flag);

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
    flag->error_occurs_stop = true;

    if (strcmp(argv[1], "-i") == 0)
    {
        flag->interactive = true;
    }

    for (int i = 2; i < argc; i++)
    {
        if (strcmp(argv[i], "-v") == 0)
        {
            flag->verbose = true;
            continue;
        }
        if (strcmp(argv[i], "-c") == 0)
        {
            flag->error_occurs_stop = false;
            continue;
        }
        if (strcmp(argv[i], "-i") == 0)
        {
            // The -i flag is already handled but we want to allow duplicate flags
            continue;
        }

        perror("An unknown flag was given");
        exit(EXIT_FAILURE);
    }
    return flag;
}

static void activate_flags(flags *flag)
{
    verbose = flag->verbose;
    interactive = flag->interactive;
    error_occurs_stop = flag->error_occurs_stop;

    free(flag);
}
