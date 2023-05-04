#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "file_manager.h"
#include "flag_manager.h"
#include "string_utils.h"

char *out_stream_path;
FILE *out_stream;

typedef struct flags
{
    bool verbose;
    bool interactive;
    bool error_occurs_stop;
    char *output_file;
} flags;

static flags *parse_flags(int, char *[]);
static void activate_flags(flags *);

void initialize_flags(int argc, char *argv[])
{
    flags *flag = parse_flags(argc, argv);
    activate_flags(flag);
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

        // By default interactive implies verbose
        flag->verbose = true;
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
        if (starts_with(argv[i], "-o="))
        {
            flag->output_file = argv[i] + 3;
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

    if (flag->output_file != NULL)
    {
        out_stream_path = flag->output_file;
        out_stream = open_file(out_stream_path, "w");
        if (out_stream == NULL)
        {
            exit(EXIT_FAILURE);
        }
    }

    free(flag);
}
