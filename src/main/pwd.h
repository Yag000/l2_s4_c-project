#ifndef PWD_H
#define PWD_H

#include "command.h"
#include "tree_dir_core.h"

int pwd(const command *cmd);

char *get_absolute_path_of_node(noeud *node);
char **get_list_of_noeud_above_node(noeud *node, unsigned number_of_parent);
unsigned get_number_of_node_in_absolute_path(noeud *node);

#endif