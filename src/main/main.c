#include <stdlib.h>

#include "parser.h"
#include "constants.h"
#include "tree_dir_core.h"
#include "command.h"
#include "file_manager.h"

FILE *out_stream;
char *out_stream_path = "src/main/output/output.txt";

bool verbose = false;
noeud *current_node;

int main(int argc, char *argv[])
{
    if (reset_file(out_stream_path) != 0)
    {
        return -1;
    }

    out_stream = open_file(out_stream_path, "a");

    if (out_stream == NULL)
    {
        return -1;
    }

    if (argc != 2)
    {
        perror("Nombre d'arguments incorrect");
        return -1;
    }

    current_node = create_root_noeud();
    int error_code = parse_file(argv[1]);

    destroy_noeud(current_node->racine);

    if (close_file(out_stream, out_stream_path) != 0)
    {
        return EXIT_FAILURE;
    }

    return error_code == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
