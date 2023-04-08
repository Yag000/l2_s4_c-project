#include <stdlib.h>
#include <stdio.h>

#include "parser.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        perror("Nombre d'arguments incorrect");
        return -1;
    }

    int error_code = parse_file(argv[1]);
    return error_code == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
