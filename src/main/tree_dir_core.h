#ifndef TREE_DIR_CORE_H
#define TREE_DIR_CORE_H

#include <stdbool.h>

typedef struct noeud
{
    bool est_dossier ;
    char nom [100];
    struct noeud * pere ;
    struct noeud * racine ;
    struct liste_noeud * fils ;
} noeud;

typedef struct liste_noeud {
    struct noeud * no ;
    struct liste_noeud * succ ;
} liste_noeud;

noeud* create_noeud();
void destroy_noeud(noeud* node);
bool are_equal(noeud* node1, noeud* node2);
liste_noeud *create_liste_noeud();
void destroy_liste_noeud(liste_noeud* node);
bool contains_liste_noeud(noeud* node);
bool append_liste_noeud(noeud* node);
bool remove_liste_noeud(noeud* node);

#endif