#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "constants.h"
#include "tree_dir_core.h"

FILE *out_stream;
bool verbose = false;
noeud *constant_node;

int main(int argc, char *argv[])
{

    out_stream = stdout;

    if (argc != 2)
    {
        perror("Nombre d'arguments incorrect");
        return -1;
    }

    constant_node = create_root_noeud();
    int error_code = parse_file(argv[1]);

    destroy_noeud(constant_node);

    return error_code == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
