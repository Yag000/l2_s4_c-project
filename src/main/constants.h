#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdio.h>
#include <stdbool.h>

extern FILE *out_stream;
extern bool verbose;

extern const int FATAL_ERROR;  // Error code that indicates that he program should stop
extern const int INVALID_NAME; // Error code that indicates that the name of a node is invalid

#endif