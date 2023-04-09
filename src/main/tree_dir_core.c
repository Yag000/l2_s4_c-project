#include <stdlib.h>
#include <string.h>

#include "tree_dir_core.h"

noeud *create_empty_noeud()
{
    noeud *node = malloc(sizeof(noeud));

    return node;
}

noeud *create_noeud(bool est_dossier, char *nom, noeud *pere)
{
    noeud *node = create_empty_noeud();

    int length_nom = strlen(nom);

    if (length_nom > MAX_LENGTH_NOM - 1)
    {
        length_nom = MAX_LENGTH_NOM - 1;
    }

    memmove(node->nom, nom, length_nom);
    node->nom[length_nom] = '\0';

    node->est_dossier = est_dossier;
    node->pere = pere;
    if (pere != NULL)
    {
        node->racine = pere->racine;
        return;
    }
    node->racine = NULL;
    node->fils = NULL;
}

noeud *create_noeud_with_fils(bool est_dossier, char *nom, noeud *pere, liste_noeud *fils)
{
    noeud *node = create_noeud(est_dossier, nom, pere);

    node->fils = fils;
}

noeud *create_root_noeud(char *nom)
{
    noeud *node = create_noeud(true, nom, NULL);
    node->pere = node;
    node->racine = node;
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
    if (strcmp(node1->nom, node2->nom) == 0)
    {
        return true;
    }
    return false;
}

bool is_fils_of_noeud_empty(noeud *node)
{
    if (node == NULL)
    {
        return true;
    }
    return node->fils == NULL;
}

bool contains_noeud(noeud *pere, noeud *fils)
{
    if (pere == NULL)
    {
        return false;
    }
    return contains_liste_noeud(pere->fils, fils);
}

unsigned get_number_of_fils(noeud *noeud)
{
    if (noeud == NULL)
    {
        return;
    }
    return size_liste_noeud(noeud->fils);
}

noeud *get_a_fils_of_noeud(noeud *node, const char *name)
{
    if (node == NULL || !node->est_dossier)
    {
        return NULL;
    }
    return get_liste_noeud(node->fils, name);
}

bool append_a_fils_to_noeud(noeud *pere, noeud *fils)
{
    if (pere == NULL || fils == NULL)
    {
        return false;
    }
    if (!pere->est_dossier)
    {
        return false;
    }
    bool append_success;

    if (pere->fils == NULL)
    {
        pere->fils = create_liste_noeud(fils);
        append_success = true;
    }
    else
    {
        append_success = append_liste_noeud(pere->fils, fils);
    }
    if (append_success)
    {
        fils->pere = pere;
        fils->racine = pere->racine;
    }
    return append_success;
}

bool remove_a_fils_of_noeud(noeud *pere, noeud *fils)
{
    if (pere == NULL || fils == NULL || !pere->est_dossier)
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
    node_list->succ = NULL;
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

unsigned size_liste_noeud(liste_noeud *node_list)
{
    if (node_list == NULL)
    {
        return 0;
    }
    return 1 + size_liste_noeud(node_list->succ);
}

noeud *get_liste_noeud(liste_noeud *node_list, const char *name)
{
    if (node_list == NULL)
    {
        return NULL;
    }
    if (strcmp(node_list->no->nom, name))
    {
        return node_list->no;
    }
    return get_liste_noeud(node_list->succ, name);
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
        node_list->succ = create_liste_noeud(node);
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
