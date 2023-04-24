#include <stdlib.h>

#include "parser.h"
#include "constants.h"

FILE *out_stream;
bool verbose = false;

int main(int argc, char *argv[])
{

    out_stream = stdout;

    if (argc != 2)
    {
        perror("Nombre d'arguments incorrect");
        return -1;
    }

    int error_code = parse_file(argv[1]);
    return error_code == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
