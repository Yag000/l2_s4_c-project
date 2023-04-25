#ifndef TREE_DIR_CORE_H
#define TREE_DIR_CORE_H

#include <stdbool.h>

#define MAX_LENGTH_NOM 100

typedef struct noeud
{
    bool est_dossier;
    char nom[MAX_LENGTH_NOM];
    struct noeud *pere;
    struct noeud *racine;
    struct liste_noeud *fils;
} noeud;

typedef struct liste_noeud
{
    struct noeud *no;
    struct liste_noeud *succ;
} liste_noeud;

extern noeud *current_node;

noeud *create_noeud(bool est_dossier, const char *nom, noeud *pere);
noeud *create_noeud_with_fils(bool est_dossier, const char *nom, noeud *pere, liste_noeud *fils);
noeud *create_root_noeud();
void destroy_noeud(noeud *node);
bool are_noeuds_equal(const noeud *node1, const noeud *node2);
bool is_root_node(const noeud *node);
bool is_fils_of_noeud_empty(const noeud *node);
bool contains_noeud(noeud *pere, noeud *fils);
unsigned get_number_of_fils(noeud *noeud);
noeud *get_a_fils_of_noeud(noeud *node, const char *name);
bool append_a_fils_to_noeud(noeud *pere, noeud *fils);
bool remove_a_node_from_fils(noeud *pere, noeud *fils);
bool remove_a_fils_of_noeud(noeud *parent, const char *name);

liste_noeud *create_liste_noeud(noeud *node);
void destroy_liste_noeud(liste_noeud *node_list);
bool contains_liste_noeud(liste_noeud *node_list, noeud *node);
unsigned size_liste_noeud(liste_noeud *node_list);
noeud *get_liste_noeud(liste_noeud *node_list, const char *name);
bool append_liste_noeud(liste_noeud *node_list, noeud *node);
liste_noeud *remove_liste_noeud(liste_noeud *node_list, noeud *node);

char *get_absolute_path_of_node(const noeud *node);
void destroy_root();

#endif