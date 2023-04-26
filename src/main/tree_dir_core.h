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

noeud *create_noeud(bool, const char *, noeud *);
noeud *create_noeud_with_fils(bool, const char *, noeud *, liste_noeud *);
noeud *create_root_noeud();
void destroy_noeud(noeud *);
bool are_noeuds_equal(const noeud *, const noeud *);
bool is_root_node(const noeud *);
bool is_fils_of_noeud_empty(const noeud *);
bool contains_noeud(noeud *, noeud *);
unsigned get_number_of_fils(noeud *);
noeud *get_a_fils_of_noeud(noeud *, const char *);
bool append_a_fils_to_noeud(noeud *, noeud *);
bool remove_a_node_from_fils(noeud *, noeud *);
bool remove_a_fils_of_noeud(noeud *, const char *);

liste_noeud *create_liste_noeud(noeud *);
void destroy_liste_noeud(liste_noeud *);
bool contains_liste_noeud(liste_noeud *, noeud *);
unsigned size_liste_noeud(liste_noeud *);
noeud *get_a_noeud_in_liste_noeud(liste_noeud *, const char *);
bool append_liste_noeud(liste_noeud *, noeud *);
liste_noeud *remove_liste_noeud(liste_noeud *, noeud *);

void destroy_root();

char *get_absolute_path_of_node(const noeud *);
noeud *search_node_in_tree(noeud *, char *);


noeud *get_new_node_from_path(noeud *, char *, bool );
#endif
