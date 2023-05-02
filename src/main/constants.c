#include "constants.h"

bool interactive = false;

const int EXIT_PROGRAM_SUCCESS = -2;  // Error code that indicates that the program executed successfully and that
                                      // it should be terminated
const int SUCCESS = 0;                // Error code that indicates that the program executed successfully
const int FATAL_ERROR = -1;           // Error code that indicates that he program should stop
const int INVALID_NAME = 1;           // Error code that indicates that the name of a node is invalid
const int INVALID_PATH = 2;           // Error code that indicates that the path of a node is invalid
const int INVALID_NUMBER_OF_ARGS = 3; // Error code that indicates that the number of arguments is invalid
const int INVALID_SELECTION = 4;      // Error code that indicates that the element selected by the user is invalid
