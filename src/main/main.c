#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "constants.h"
#include "tree_dir_core.h"

FILE *out_stream;

bool verbose = false;
noeud *current_node;

int main(int argc, char *argv[])
{
    out_stream = stdout;
    verbose = false;

    if (argc != 2)
    {
        if (argc == 3 && strcmp(argv[2], "-v") == 0)
        {
            verbose = true;
        }
        else
        {
            perror("Nombre d'arguments incorrect");
            return -1;
        }
    }

    current_node = create_root_noeud();

    int error_code = parse_file(argv[1]);

    destroy_noeud(current_node->racine);

    return error_code == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
