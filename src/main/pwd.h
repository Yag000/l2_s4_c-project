#ifndef PWD_H
#define PWD_H

#include "command.h"
#include "tree_dir_core.h"

int pwd(const command *cmd);

char *get_absolute_path_of_node(noeud *node);

#endif