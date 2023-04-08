#ifndef TREE_DIR_CORE_H
#define TREE_DIR_CORE_H

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

#endif