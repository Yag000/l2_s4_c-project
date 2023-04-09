#include <stdlib.h>
#include <string.h>

#include "tree_dir_core.h"

noeud *create_empty_noeud()
{
    noeud *node = malloc(sizeof(noeud));

    return node;
}

noeud *create_noeud(bool est_dossier, char *nom, noeud *pere, noeud *racine)
{
    noeud *node = create_empty_noeud();

    int length_nom = strlen(nom);

    if (length_nom > MAX_LENGTH_NOM - 1)
    {
        length_nom = MAX_LENGTH_NOM - 1;
    }

    memmove(node->nom, nom, length_nom);
    node->nom[length_nom] = '0';

    node->est_dossier = est_dossier;
    node->pere = pere;
    node->racine = racine;
}

noeud *create_noeud_with_fils(bool est_dossier, char *nom, noeud *pere, noeud *racine, liste_noeud *fils)
{
    noeud *node = create_noeud(est_dossier, nom, pere, racine);

    node->fils = fils;
}

void destroy_noeud(noeud *node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->est_dossier && node->fils != NULL)
    {
        destroy_liste_noeud(node->fils);
    }
    free(node);
}

bool are_noeud_equal(noeud *node1, noeud *node2)
{
    // TODO (should have the path)

    if (node1 == NULL || node2 == NULL)
    {
        return false;
    }

    return strcmp(node1->nom, node2->nom);
}

bool is_fils_of_node_empty(noeud *node)
{
    if (node == NULL)
    {
        return true;
    }
    return node->fils == NULL;
}

bool append_a_fils_to_noeud(noeud *pere, noeud *fils)
{
    if (!pere->est_dossier)
    {
        return false;
    }
    if (pere->fils == NULL)
    {
        pere->fils = create_liste_noeud(fils);
        return true;
    }
    return append_liste_noeud(pere->fils, fils);
}

bool remove_a_fils_of_noeud(noeud *pere, noeud *fils)
{
    if (!pere->est_dossier)
    {
        return false;
    }
    if (!contains_liste_noeud(pere->fils, fils))
    {
        return false;
    }
    remove_liste_noeud(pere, fils);
    return true;
}

liste_noeud *create_liste_noeud(noeud *node)
{
    liste_noeud *node_list = malloc(sizeof(liste_noeud));

    node_list->no = node;
}

void destroy_liste_noeud(liste_noeud *node_list)
{
    if (node_list == NULL)
    {
        return;
    }
    destroy_liste_noeud(node_list->succ);
    destroy_noeud(node_list->no);

    free(node_list);
}

bool contains_liste_noeud(liste_noeud *node_list, noeud *node)
{
    if (node_list == NULL)
    {
        return false;
    }
    if (are_noeud_equal(node_list->no, node))
    {
        return true;
    }
    return contains_liste_noeud(node_list->succ, node);
}

bool append_liste_noeud(liste_noeud *node_list, noeud *node)
{
    if (node_list == NULL)
    {
        return false;
    }
    if (are_noeud_equal(node_list->no, node))
    {
        return false;
    }
    if (node_list->succ == NULL)
    {
        liste_noeud *succ = create_liste_noeud(node);
        return true;
    }
    return append_liste_noeud(node_list->succ, node);
}

liste_noeud *remove_liste_noeud(liste_noeud *node_list, noeud *node)
{
    if (node_list == NULL)
    {
        return NULL;
    }
    if (are_noeud_equal(node_list->no, node))
    {
        liste_noeud *acc = node_list->succ;
        free(node_list);
        return acc;
    }
    node_list->succ = remove_liste_noeud(node_list, node);
    return node_list;
}
