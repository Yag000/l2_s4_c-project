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

noeud *create_empty_noeud();
noeud *create_noeud(bool est_dossier, char *nom, noeud *pere, noeud *racine);
noeud *create_noeud_with_fils(bool est_dossier, char *nom, noeud *pere, noeud *racine, liste_noeud *fils);
void destroy_noeud(noeud *node);
bool are_noeud_equal(noeud *node1, noeud *node2);
bool is_fils_of_node_empty(noeud *node);
liste_noeud *create_liste_noeud(noeud *node);
void destroy_liste_noeud(liste_noeud *node_list);
bool contains_liste_noeud(liste_noeud *node_list, noeud *node);
bool append_liste_noeud(liste_noeud *node_list, noeud *node);
bool remove_liste_noeud(liste_noeud *node);

#endif