#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "file_manager.h"
#include "flag_manager.h"
#include "parser.h"
#include "string_utils.h"
#include "tree_dir_core.h"

noeud *current_node;

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

    current_node = create_root_noeud();

    int error_code = parse_file(argv[1]);

    destroy_tree();

    return error_code == SUCCESS || error_code == EXIT_PROGRAM_SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE;
}
