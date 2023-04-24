#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "tree_dir_core.h"
#include "string_utils.h"

noeud *create_empty_noeud()
{
    noeud *node = malloc(sizeof(noeud));

    assert(node != NULL);

    return node;
}

noeud *create_noeud(bool est_dossier, const char *nom, noeud *pere)
{
    assert(strcmp(nom, "") != 0 && strcmp(nom, ".") != 0 && strcmp(nom, "..") != 0);

    noeud *node = create_empty_noeud();

    int length_nom = strlen(nom);

    if (length_nom > MAX_LENGTH_NOM - 1)
    {
        length_nom = MAX_LENGTH_NOM - 1;
    }

    memmove(node->nom, nom, length_nom);
    node->nom[length_nom] = '\0';

    node->est_dossier = est_dossier;
    node->fils = NULL;

    if (pere == NULL)
    {
        node->pere = node;
        node->racine = node;
        return node;
    }
    node->pere = pere;
    node->racine = pere->racine;
    return node;
}

noeud *create_noeud_with_fils(bool is_directory, const char *name, noeud *parent, liste_noeud *children)
{
    noeud *node = create_noeud(is_directory, name, parent);

    node->fils = children;

    return node;
}

/*
Create a node with pere and racine set to himself
*/
noeud *create_root_noeud()
{
    noeud *node = create_empty_noeud();

    node->nom[0] = '\0';
    node->pere = node;
    node->racine = node;
    node->est_dossier = true;
    node->fils = NULL;

    return node;
}

void destroy_noeud(noeud *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->est_dossier)
    {
        destroy_liste_noeud(node->fils);
    }
    free(node);
}

/*
Return true (for the moment) if the nodes have the same name
*/
bool are_noeuds_equal(const noeud *node1, const noeud *node2)
{
    if (node1 == NULL && node2 == NULL)
    {
        return true;
    }

    if (node1 == NULL || node2 == NULL)
    {
        return false;
    }

    return node1 == node2;
}

bool is_root_node(const noeud *node)
{
    if (node == NULL)
    {
        return false;
    }
    return (strcmp(node->nom, "") == 0) && node == node->pere && node == node->racine;
}

bool is_fils_of_noeud_empty(const noeud *node)
{
    if (node == NULL)
    {
        return true;
    }
    return node->fils == NULL;
}

/*
Return true if the node pere contains node in these own fils
*/
bool contains_noeud(noeud *parent, noeud *node)
{
    if (parent == NULL)
    {
        return false;
    }
    return contains_liste_noeud(parent->fils, node);
}

unsigned get_number_of_fils(noeud *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return size_liste_noeud(node->fils);
}

/*
Return the node that has its nom equal to name
*/
noeud *get_a_fils_of_noeud(noeud *node, const char *name)
{
    if (node == NULL || !node->est_dossier)
    {
        return NULL;
    }
    return get_liste_noeud(node->fils, name);
}

/*
Return true if the child node has been appended to parent
Otherwise, return false if the node parent already contains node
or if it's not a directory
*/
bool append_a_fils_to_noeud(noeud *parent, noeud *node)
{
    if (parent == NULL || node == NULL || !parent->est_dossier)
    {
        return false;
    }

    bool append_success;

    if (parent->fils == NULL)
    {
        parent->fils = create_liste_noeud(node);
        append_success = true;
    }
    else
    {
        append_success = append_liste_noeud(parent->fils, node);
    }

    if (append_success)
    {
        node->pere = parent;
        node->racine = parent->racine;
    }
    return append_success;
}

/*
Return true if node has been removed from the fils of parent
Otherwise, return false if parent did not contain it or if
it's not a directory
*/
bool remove_a_node_from_fils(noeud *parent, noeud *node)
{
    if (parent == NULL || node == NULL || !parent->est_dossier)
    {
        return false;
    }

    if (!contains_liste_noeud(parent->fils, node))
    {
        return false;
    }

    parent->fils = remove_liste_noeud(parent->fils, node);

    return true;
}

/*
Return true if node has been removed from the fils of parent
and has been destroyed
Otherwise, return false if parent did not contain it or if
it's not a directory
*/
bool remove_a_fils_of_noeud(noeud *parent, const char *name)
{
    if (parent == NULL || !parent->est_dossier)
    {
        return false;
    }
    noeud *node = get_liste_noeud(parent->fils, name);

    if (node == NULL)
    {
        return false;
    }
    parent->fils = remove_liste_noeud(parent->fils, node);
    destroy_noeud(node);

    return true;
}

liste_noeud *create_liste_noeud(noeud *node)
{
    liste_noeud *node_list = malloc(sizeof(liste_noeud));

    assert(node_list != NULL);

    node_list->no = node;
    node_list->succ = NULL;

    return node_list;
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

/*
Return true if the liste_noeud node_list contains node
*/
bool contains_liste_noeud(liste_noeud *node_list, noeud *node)
{
    if (node_list == NULL)
    {
        return false;
    }

    if (are_noeuds_equal(node_list->no, node))
    {
        return true;
    }

    return contains_liste_noeud(node_list->succ, node);
}

/*
Return the number of node in node_list
*/
unsigned size_liste_noeud(liste_noeud *node_list)
{
    if (node_list == NULL)
    {
        return 0;
    }

    return 1 + size_liste_noeud(node_list->succ);
}

/*
Return a node in node_list which has these nom equals to name
Return NULL otherwise
*/
noeud *get_liste_noeud(liste_noeud *node_list, const char *name)
{
    if (node_list == NULL)
    {
        return NULL;
    }

    if (strcmp(node_list->no->nom, name) == 0)
    {
        return node_list->no;
    }

    return get_liste_noeud(node_list->succ, name);
}

/*
Return true if the append of node in node_list succeeds
Otherwise, return false if the node already exists in node_list
*/
bool append_liste_noeud(liste_noeud *node_list, noeud *node)
{
    if (node_list == NULL || strcmp(node_list->no->nom, node->nom) == 0)
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

/*
Return the new list without node if it founds node
Free the list removed (but don't free the node)
*/
liste_noeud *remove_liste_noeud(liste_noeud *node_list, noeud *node)
{
    if (node_list == NULL)
    {
        return NULL;
    }

    if (are_noeuds_equal(node_list->no, node))
    {
        liste_noeud *acc = node_list->succ;

        // !WARNING! here, just the list is free, the user must free the node himself
        free(node_list);

        return acc;
    }

    node_list->succ = remove_liste_noeud(node_list->succ, node);

    return node_list;
}

/**
 * Returns the string containing the absolute path of the node
 */
char *get_absolute_path_of_node(const noeud *node)
{
    assert(node != NULL);

    char *absolute_path;

    if (is_root_node(node))
    {
        absolute_path = malloc(2 * sizeof(char));
        absolute_path[0] = '/';
        absolute_path[1] = '\0';

        return absolute_path;
    }

    if (is_root_node(node->pere))
    {
        char *root_path = malloc(sizeof(char));
        root_path[0] = '\0';

        absolute_path = concat_two_words_with_delimiter(root_path, node->nom, '/');

        free(root_path);

        return absolute_path;
    }

    char *parent_absolute_path = get_absolute_path_of_node(node->pere);
    absolute_path = concat_two_words_with_delimiter(parent_absolute_path, node->nom, '/');

    free(parent_absolute_path);

    return absolute_path;
}

void destroy_root()
{
    assert(current_node != NULL);
    assert(current_node->racine != NULL);

    destroy_noeud(current_node->racine);
}
