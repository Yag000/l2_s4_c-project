#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "file_manager.h"
#include "flag_manager.h"
#include "parser.h"
#include "tree_dir_core.h"

node *current_node;

int main(int argc, char *argv[])
{

    out_stream = stdout;
    out_stream_path = NULL;

    // Hnadle 0 arguments
    if (argc <= 1)
    {
        perror("No argument was given");
        return EXIT_FAILURE;
    }

    initialize_flags(argc, argv);

    current_node = create_root_node();

    int error_code = parse_file(argv[1]);

    if (out_stream != stdout)
    {
        close_file(out_stream, out_stream_path);
    }
    if (command_record_stream != NULL)
    {
        close_file(command_record_stream, command_record_path);
    }

    destroy_tree();

    if (error_code == EXIT_PROGRAM_SUCCESS || error_code == SUCCESS || error_code == EMPTY_COMMAND)
    {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
