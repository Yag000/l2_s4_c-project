#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <stdbool.h>

extern FILE *out_stream;
extern bool verbose;
extern char *out_stream_path;

extern const int SUCCESS;                // Error code that indicates that the program executed successfully
extern const int FATAL_ERROR;            // Error code that indicates that he program should stop
extern const int INVALID_NAME;           // Error code that indicates that the name of a node is invalid
extern const int INVALID_PATH;           // Error code that indicates that the path of a node is invalid
extern const int INVALID_NUMBER_OF_ARGS; // Error code that indicates that the number of arguments is invalid
extern const int INVALID_SELECTION;      // Error code that indicates that the element selected by the user is invalid

#endif