#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "string_utils.h"
#include "tree_dir_core.h"

static noeud *search_node(noeud *, char *, bool, bool);
static noeud *search_node_in_tree_with_iterator(noeud *, string_iterator *, bool, bool);

static noeud *create_empty_noeud()
{
    noeud *node1 = malloc(sizeof(noeud));

    assert(node1 != NULL);

    return node1;
}

/*
Returns the node if nom is a valid name
Otherwise it returns NULL
*/
noeud *create_noeud(bool est_dossier, const char *nom, noeud *pere)
{
    assert(pere != NULL);

    noeud *node1 = create_empty_noeud();

    int length_nom = strlen(nom);

    if (length_nom > MAX_LENGTH_NOM - 1)
    {
        length_nom = MAX_LENGTH_NOM - 1;
    }

    memmove(node1->nom, nom, length_nom);
    assert(node1->nom != NULL);
    node1->nom[length_nom] = '\0';

    node1->est_dossier = est_dossier;
    node1->fils = NULL;

    if (pere == NULL)
    {
        node1->pere = node1;
        node1->racine = node1;
        return node1;
    }
    node1->pere = pere;
    node1->racine = pere->racine;
    return node1;
}

/*
Returns true if a node name is valid. In this context, a valid name is a name
that contains only alphanumeric characters.
*/
bool is_valid_name_node(const char *name) { return is_alphanumeric(name); }

noeud *create_noeud_with_fils(bool is_directory, const char *name, noeud *parent, liste_noeud *children)
{
    noeud *node1 = create_noeud(is_directory, name, parent);

    node1->fils = children;

    return node1;
}

/*
Creates a node with pere and racine set to himself. It will represent the root
of our file system.
*/
noeud *create_root_noeud()
{
    noeud *node1 = create_empty_noeud();

    node1->nom[0] = '\0';
    node1->pere = node1;
    node1->racine = node1;
    node1->est_dossier = true;
    node1->fils = NULL;

    return node1;
}

void destroy_noeud(noeud *node1)
{
    assert(node1 != NULL);

    if (node1->est_dossier)
    {
        destroy_liste_noeud(node1->fils);
    }
    free(node1);
}

/*
Returns true if the nodes are equal (same address).
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

bool is_root_node(const noeud *node1)
{
    if (node1 == NULL)
    {
        return false;
    }
    return (strcmp(node1->nom, "") == 0) && node1 == node1->pere && node1 == node1->racine;
}

bool is_fils_of_noeud_empty(const noeud *node1)
{
    if (node1 == NULL)
    {
        return true;
    }
    return node1->fils == NULL;
}

/*
Returns true if the node pere contains node in his own fils.
*/
bool contains_noeud(noeud *parent, noeud *node1)
{
    if (parent == NULL)
    {
        return false;
    }
    return contains_liste_noeud(parent->fils, node1);
}

unsigned get_number_of_fils(noeud *node1)
{
    assert(node1 != NULL);

    return size_liste_noeud(node1->fils);
}

/*
Returns the node that has its nom equal to name.
*/
noeud *get_a_fils_of_noeud(noeud *node1, const char *name)
{
    assert(node1 != NULL && name != NULL);

    if (!node1->est_dossier)
    {
        return NULL;
    }
    return get_a_noeud_in_liste_noeud(node1->fils, name);
}

/*
Appends node to the fils of parent. If the append is successful,
it will return true, otherwise it will return false.
The append will be successful the parent is a directory and does
not already contain node.
*/
int append_a_fils_to_noeud(noeud *parent, noeud *node1)
{
    assert(parent != NULL && node1 != NULL);

    if (!parent->est_dossier)
    {
        return INVALID_SELECTION;
    }

    int append_error_value;

    if (parent->fils == NULL)
    {
        parent->fils = create_liste_noeud(node1);

        append_error_value = SUCCESS;
    }
    else
    {
        append_error_value = append_liste_noeud(parent->fils, node1);
    }

    if (append_error_value == SUCCESS)
    {
        node1->pere = parent;
        node1->racine = parent->racine;
    }
    return append_error_value;
}

/*
Returns true if node has been removed from the fils of parent
Otherwise, return false. If parent did not contain node or if
the parent is not a directory it will fail.
*/
int remove_a_node_from_fils(noeud *parent, noeud *node1)
{
    assert(parent != NULL && node1 != NULL);

    if (!parent->est_dossier)
    {
        return INVALID_SELECTION;
    }

    if (!contains_liste_noeud(parent->fils, node1))
    {
        return INVALID_SELECTION;
    }

    parent->fils = remove_liste_noeud(parent->fils, node1);

    return SUCCESS;
}

/*
Returns true if node has been removed from the fils of parent
and has been destroyed. Otherwise, return false.
If parent did not contain it or if the parent is not a directory it will fail.
*/
int remove_a_fils_of_noeud(noeud *parent, const char *name)
{
    assert(parent != NULL);

    if (!parent->est_dossier)
    {
        return INVALID_SELECTION;
    }

    noeud *node1 = get_a_noeud_in_liste_noeud(parent->fils, name);

    if (node1 == NULL)
    {
        return INVALID_SELECTION;
    }
    parent->fils = remove_liste_noeud(parent->fils, node1);
    destroy_noeud(node1);

    return SUCCESS;
}

liste_noeud *create_liste_noeud(noeud *node1)
{
    assert(node1 != NULL);

    liste_noeud *node_list = malloc(sizeof(liste_noeud));

    assert(node_list != NULL);

    node_list->no = node1;
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
Returns true if node_list contains node.
*/
bool contains_liste_noeud(liste_noeud *node_list, noeud *node1)
{
    if (node_list == NULL)
    {
        return false;
    }

    if (are_noeuds_equal(node_list->no, node1))
    {
        return true;
    }

    return contains_liste_noeud(node_list->succ, node1);
}

/*
Returns the number of nodes in node_list.
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
Returns a node in node_list which has its nom equal to name.
Return NULL otherwise.
*/
noeud *get_a_noeud_in_liste_noeud(liste_noeud *node_list, const char *name)
{
    if (node_list == NULL)
    {
        return NULL;
    }

    if (strcmp(node_list->no->nom, name) == 0)
    {
        return node_list->no;
    }

    return get_a_noeud_in_liste_noeud(node_list->succ, name);
}

/*
Returns true if the append of node in node_list succeeds.
Otherwise return false, this will happen if the node is already inside
node_list.
*/
int append_liste_noeud(liste_noeud *node_list, noeud *node1)
{
    assert(node_list != NULL);

    if (strcmp(node_list->no->nom, node1->nom) == 0)
    {
        return INVALID_NAME;
    }

    if (node_list->succ == NULL)
    {
        node_list->succ = create_liste_noeud(node1);
        return SUCCESS;
    }

    return append_liste_noeud(node_list->succ, node1);
}

/*
Returns the new list without node if it finds node.
Frees the removed list (but does not free node).
*/
liste_noeud *remove_liste_noeud(liste_noeud *node_list, noeud *node1)
{
    if (node_list == NULL)
    {
        return NULL;
    }

    if (are_noeuds_equal(node_list->no, node1))
    {
        liste_noeud *acc = node_list->succ;
        free(node_list);

        return acc;
    }

    node_list->succ = remove_liste_noeud(node_list->succ, node1);

    return node_list;
}

void destroy_tree()
{
    assert(current_node != NULL);
    assert(current_node->racine != NULL);

    destroy_noeud(current_node->racine);
}
/*
Returns the string containing the absolute path of the node.
*/
char *get_absolute_path_of_node(const noeud *node1)
{
    assert(node1 != NULL);

    char *absolute_path;

    if (is_root_node(node1))
    {
        absolute_path = malloc(2 * sizeof(char));
        assert(absolute_path != NULL);
        absolute_path[0] = '/';
        absolute_path[1] = '\0';

        return absolute_path;
    }

    if (is_root_node(node1->pere))
    {
        char *root_path = malloc(sizeof(char));
        assert(root_path != NULL);
        root_path[0] = '\0';

        absolute_path = concat_two_words_with_delimiter(root_path, node1->nom, '/');

        free(root_path);

        return absolute_path;
    }

    char *parent_absolute_path = get_absolute_path_of_node(node1->pere);
    absolute_path = concat_two_words_with_delimiter(parent_absolute_path, node1->nom, '/');

    free(parent_absolute_path);

    return absolute_path;
}

/*
Search a node in a tree, and if it is found, it is returned
Otherwise the function returns NULL
*/
noeud *search_node_in_tree(noeud *deb, char *path) { return search_node(deb, path, false, false); }

/*
Returns a new node in the position given by the path if it exists.
The last word represents the node's name.
*/
noeud *search_node_in_tree_with_node_creation(noeud *deb, char *path, bool is_directory)
{
    return search_node(deb, path, true, is_directory);
}

/*
Utility method for search_node_in_tree_with_name and search_node_in_tree.
*/
static noeud *search_node(noeud *deb, char *path, bool is_name_included, bool is_directory)
{
    assert(deb != NULL);

    unsigned len_path = strlen(path);

    if (len_path == 0)
    {
        return NULL;
    }

    if (path[len_path - 1] == '/')
    {
        return NULL;
    }

    string_iterator *iterator = create_string_iterator(path, '/');

    if (path[0] == '/')
    {
        deb = deb->racine;
    }

    noeud *result = search_node_in_tree_with_iterator(deb, iterator, is_name_included, is_directory);

    destroy_string_iterator(iterator);

    return result;
}

/*
Search a node in a tree with the iteration of iterator until its end
If the iteration is ".", applies the function to the same node
If the iteration is "..", applies the function to the parent of node
If the iteration is not found in fils of node, returns NULL
If the name is included then it will stop before reaching the end of
the path and return a noeud with it's nom as the last word of the path.
Otherwise applies the function to the found child
*/
static noeud *search_node_in_tree_with_iterator(noeud *node1, string_iterator *iterator, bool is_name_included,
                                                bool is_directory)
{
    if (!has_next_word(iterator) && !is_name_included)
    {
        return node1;
    }
    if (!node1->est_dossier)
    {
        return NULL;
    }

    char *name = next_word(iterator);

    if (!has_next_word(iterator) && is_name_included)
    {

        noeud *result = create_noeud(is_directory, name, node1);

        free(name);
        return result;
    }

    if (strcmp(name, ".") == 0)
    {
        free(name);

        return search_node_in_tree_with_iterator(node1, iterator, is_name_included, is_directory);
    }

    if (strcmp(name, "..") == 0)
    {
        free(name);

        if (node1->pere == NULL)
        {
            return NULL;
        }
        return search_node_in_tree_with_iterator(node1->pere, iterator, is_name_included, is_directory);
    }

    noeud *next_node = get_a_fils_of_noeud(node1, name);

    free(name);

    if (next_node == NULL)
    {
        return NULL;
    }

    return search_node_in_tree_with_iterator(next_node, iterator, is_name_included, is_directory);
}

/*
Returns true if the node2 is a parent of node.
 */
bool is_noeud_inside(const noeud *node1, const noeud *node2)
{
    if (node1 == NULL || node2 == NULL)
    {
        return false;
    }

    if (is_root_node(node2))
    {
        return true;
    }

    while (!is_root_node(node1))
    {
        if (are_noeuds_equal(node1, node2))
        {
            return true;
        }
        node1 = node1->pere;
    }

    return false;
}

/*
Returns the size of the longest name of fils of node.
*/
unsigned get_longest_name_length_of_node_fils(const noeud *node1)
{
    assert(node1 != NULL);

    if (!node1->est_dossier)
    {
        return 0;
    }
    unsigned max_len = 0;

    for (liste_noeud *lst = node1->fils; lst != NULL; lst = lst->succ)
    {
        unsigned len_name = strlen(lst->no->nom);

        if (len_name > max_len)
        {
            max_len = len_name;
        }
    }
    return max_len;
}

/*
Move the fils of node to a new node and frees.node1
*/
void move_fils_of_node_to_new_node(noeud *node1, noeud *new_node)
{
    assert(node1 != NULL && new_node != NULL);

    if (new_node->fils != NULL)
    {
        return;
    }

    new_node->fils = node1->fils;

    for (liste_noeud *lst = node1->fils; lst != NULL; lst = lst->succ)
    {
        lst->no->pere = new_node;
    }
    free(node1);
}
