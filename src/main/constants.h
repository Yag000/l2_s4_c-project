#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <stdbool.h>

extern FILE *out_stream;
extern bool verbose;

extern const int FATAL_ERROR;            // Error code that indicates that he program should stop
extern const int INVALID_NAME;           // Error code that indicates that the name of a node is invalid
extern const int INVALID_PATH;           // Error code that indicates that the path of a node is invalid
extern const int INVALID_NUMBER_OF_ARGS; // Error code that indicates that the number of arguments is invalid

#endif