#include <stdlib.h>

#include "parser.h"
#include "constants.h"
#include "tree_dir_core.h"

FILE *out_stream;

bool verbose = false;
noeud *current_node;

int main(int argc, char *argv[])
{
    out_stream = stdout;

    if (argc != 2)
    {
        perror("Nombre d'arguments incorrect");
        return EXIT_FAILURE;
    }

    current_node = create_root_noeud();
    int error_code = parse_file(argv[1]);

    destroy_root();

    return error_code == SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE;
}
