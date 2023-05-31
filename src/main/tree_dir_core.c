#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "string_utils.h"
#include "tree_dir_core.h"

static node *search_node(node *, char *, bool, bool);
static node *search_node_in_tree_with_iterator(node *, string_iterator *, bool, bool);

static node *create_empty_node()
{
    node *node1 = malloc(sizeof(node));

    assert(node1 != NULL);

    return node1;
}

/*
Returns the node if name is a valid name
Otherwise it returns NULL
*/
node *create_node(bool is_directory, const char *name, node *parent)
{
    assert(parent != NULL);

    node *node1 = create_empty_node();

    int length_name = strlen(name);

    if (length_name > MAX_LENGTH_NAME - 1)
    {
        length_name = MAX_LENGTH_NAME - 1;
    }

    memmove(node1->name, name, length_name);
    assert(node1->name != NULL);
    node1->name[length_name] = '\0';

    node1->is_directory = is_directory;
    node1->children = NULL;

    if (parent == NULL)
    {
        node1->parent = node1;
        node1->root = node1;
        return node1;
    }
    node1->parent = parent;
    node1->root = parent->root;
    return node1;
}

/*
Returns true if a node name is valid. In this context, a valid name is a name
that contains only alphanumeric characters.
*/
bool is_valid_name_node(const char *name) { return is_alphanumeric(name); }

node *create_node_with_children(bool is_directory, const char *name, node *parent, liste_node *children)
{
    node *node1 = create_node(is_directory, name, parent);

    node1->children = children;

    return node1;
}

/*
Creates a node with parent and root set to himself. It will represent the root
of our file system.
*/
node *create_root_node()
{
    node *node1 = create_empty_node();

    node1->name[0] = '\0';
    node1->parent = node1;
    node1->root = node1;
    node1->is_directory = true;
    node1->children = NULL;

    return node1;
}

void destroy_node(node *node1)
{
    assert(node1 != NULL);

    if (node1->is_directory)
    {
        destroy_liste_node(node1->children);
    }
    free(node1);
}

/*
Returns true if the nodes are equal (same address).
*/
bool are_nodes_equal(const node *node1, const node *node2)
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

bool is_root_node(const node *node1)
{
    if (node1 == NULL)
    {
        return false;
    }
    return (strcmp(node1->name, "") == 0) && node1 == node1->parent && node1 == node1->root;
}

bool is_children_of_node_empty(const node *node1)
{
    if (node1 == NULL)
    {
        return true;
    }
    return node1->children == NULL;
}

/*
Returns true if the node parent contains node in his own children.
*/
bool contains_node(node *parent, node *node1)
{
    if (parent == NULL)
    {
        return false;
    }
    return contains_liste_node(parent->children, node1);
}

unsigned get_number_of_children(node *node1)
{
    assert(node1 != NULL);

    return size_liste_node(node1->children);
}

/*
Returns the node that has its name equal to name.
*/
node *get_a_child_of_node(node *node1, const char *name)
{
    assert(node1 != NULL && name != NULL);

    if (!node1->is_directory)
    {
        return NULL;
    }
    return get_a_node_in_liste_node(node1->children, name);
}

/*
Appends node to the children of parent. If the append is successful,
it will return true, otherwise it will return false.
The append will be successful the parent is a directory and does
not already contain node.
*/
int append_child_to_node(node *parent, node *node1)
{
    assert(parent != NULL && node1 != NULL);

    if (!parent->is_directory)
    {
        return INVALID_SELECTION;
    }

    int append_error_value;

    if (parent->children == NULL)
    {
        parent->children = create_liste_node(node1);

        append_error_value = SUCCESS;
    }
    else
    {
        append_error_value = append_liste_node(parent->children, node1);
    }

    if (append_error_value == SUCCESS)
    {
        node1->parent = parent;
        node1->root = parent->root;
    }
    return append_error_value;
}

/*
Returns true if node has been removed from the children of parent
Otherwise, return false. If parent did not contain node or if
the parent is not a directory it will fail.
*/
int remove_a_child_from_children(node *parent, node *node1)
{
    assert(parent != NULL && node1 != NULL);

    if (!parent->is_directory)
    {
        return INVALID_SELECTION;
    }

    if (!contains_liste_node(parent->children, node1))
    {
        return INVALID_SELECTION;
    }

    parent->children = remove_liste_node(parent->children, node1);

    return SUCCESS;
}

/*
Returns true if node has been removed from the children of parent
and has been destroyed. Otherwise, return false.
If parent did not contain it or if the parent is not a directory it will fail.
*/
int remove_a_child_of_node(node *parent, const char *name)
{
    assert(parent != NULL);

    if (!parent->is_directory)
    {
        return INVALID_SELECTION;
    }

    node *node1 = get_a_node_in_liste_node(parent->children, name);

    if (node1 == NULL)
    {
        return INVALID_SELECTION;
    }
    parent->children = remove_liste_node(parent->children, node1);
    destroy_node(node1);

    return SUCCESS;
}

liste_node *create_liste_node(node *node1)
{
    assert(node1 != NULL);

    liste_node *node_list = malloc(sizeof(liste_node));

    assert(node_list != NULL);

    node_list->no = node1;
    node_list->succ = NULL;

    return node_list;
}

void destroy_liste_node(liste_node *node_list)
{
    if (node_list == NULL)
    {
        return;
    }

    destroy_liste_node(node_list->succ);
    destroy_node(node_list->no);

    free(node_list);
}

/*
Returns true if node_list contains node.
*/
bool contains_liste_node(liste_node *node_list, node *node1)
{
    if (node_list == NULL)
    {
        return false;
    }

    if (are_nodes_equal(node_list->no, node1))
    {
        return true;
    }

    return contains_liste_node(node_list->succ, node1);
}

/*
Returns the number of nodes in node_list.
*/
unsigned size_liste_node(liste_node *node_list)
{
    if (node_list == NULL)
    {
        return 0;
    }

    return 1 + size_liste_node(node_list->succ);
}

/*
Returns a node in node_list which has its name equal to name.
Return NULL otherwise.
*/
node *get_a_node_in_liste_node(liste_node *node_list, const char *name)
{
    if (node_list == NULL)
    {
        return NULL;
    }

    if (strcmp(node_list->no->name, name) == 0)
    {
        return node_list->no;
    }

    return get_a_node_in_liste_node(node_list->succ, name);
}

/*
Returns true if the append of node in node_list succeeds.
Otherwise return false, this will happen if the node is already inside
node_list.
*/
int append_liste_node(liste_node *node_list, node *node1)
{
    assert(node_list != NULL);

    if (strcmp(node_list->no->name, node1->name) == 0)
    {
        return INVALID_NAME;
    }

    if (node_list->succ == NULL)
    {
        node_list->succ = create_liste_node(node1);
        return SUCCESS;
    }

    return append_liste_node(node_list->succ, node1);
}

/*
Returns the new list without node if it finds node.
Frees the removed list (but does not free node).
*/
liste_node *remove_liste_node(liste_node *node_list, node *node1)
{
    if (node_list == NULL)
    {
        return NULL;
    }

    if (are_nodes_equal(node_list->no, node1))
    {
        liste_node *acc = node_list->succ;
        free(node_list);

        return acc;
    }

    node_list->succ = remove_liste_node(node_list->succ, node1);

    return node_list;
}

void destroy_tree()
{
    assert(current_node != NULL);
    assert(current_node->root != NULL);

    destroy_node(current_node->root);
}
/*
Returns the string containing the absolute path of the node.
*/
char *get_absolute_path_of_node(const node *node1)
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

    if (is_root_node(node1->parent))
    {
        char *root_path = malloc(sizeof(char));
        assert(root_path != NULL);
        root_path[0] = '\0';

        absolute_path = concat_two_words_with_delimiter(root_path, node1->name, '/');

        free(root_path);

        return absolute_path;
    }

    char *parent_absolute_path = get_absolute_path_of_node(node1->parent);
    absolute_path = concat_two_words_with_delimiter(parent_absolute_path, node1->name, '/');

    free(parent_absolute_path);

    return absolute_path;
}

/*
Search a node in a tree, and if it is found, it is returned
Otherwise the function returns NULL
*/
node *search_node_in_tree(node *deb, char *path) { return search_node(deb, path, false, false); }

/*
Returns a new node in the position given by the path if it exists.
The last word represents the node's name.
*/
node *search_node_in_tree_with_node_creation(node *deb, char *path, bool is_directory)
{
    return search_node(deb, path, true, is_directory);
}

/*
Utility method for search_node_in_tree_with_name and search_node_in_tree.
*/
static node *search_node(node *deb, char *path, bool is_name_included, bool is_directory)
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
        deb = deb->root;
    }

    node *result = search_node_in_tree_with_iterator(deb, iterator, is_name_included, is_directory);

    destroy_string_iterator(iterator);

    return result;
}

/*
Search a node in a tree with the iteration of iterator until its end
If the iteration is ".", applies the function to the same node
If the iteration is "..", applies the function to the parent of node
If the iteration is not found in children of node, returns NULL
If the name is included then it will stop before reaching the end of
the path and return a node with it's name as the last word of the path.
Otherwise applies the function to the found child
*/
static node *search_node_in_tree_with_iterator(node *node1, string_iterator *iterator, bool is_name_included,
                                               bool is_directory)
{
    if (!has_next_word(iterator) && !is_name_included)
    {
        return node1;
    }
    if (!node1->is_directory)
    {
        return NULL;
    }

    char *name = next_word(iterator);

    if (!has_next_word(iterator) && is_name_included)
    {

        node *result = create_node(is_directory, name, node1);

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

        if (node1->parent == NULL)
        {
            return NULL;
        }
        return search_node_in_tree_with_iterator(node1->parent, iterator, is_name_included, is_directory);
    }

    node *next_node = get_a_child_of_node(node1, name);

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
bool is_node_inside(const node *node1, const node *node2)
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
        if (are_nodes_equal(node1, node2))
        {
            return true;
        }
        node1 = node1->parent;
    }

    return false;
}

/*
Returns the size of the longest name of children of node.
*/
unsigned get_longest_name_length_of_node_children(const node *node1)
{
    assert(node1 != NULL);

    if (!node1->is_directory)
    {
        return 0;
    }
    unsigned max_len = 0;

    for (liste_node *lst = node1->children; lst != NULL; lst = lst->succ)
    {
        unsigned len_name = strlen(lst->no->name);

        if (len_name > max_len)
        {
            max_len = len_name;
        }
    }
    return max_len;
}

/*
Move the children of node to a new node and frees.node1
*/
void move_children_of_node_to_new_node(node *node1, node *new_node)
{
    assert(node1 != NULL && new_node != NULL);

    if (new_node->children != NULL)
    {
        return;
    }

    new_node->children = node1->children;

    for (liste_node *lst = node1->children; lst != NULL; lst = lst->succ)
    {
        lst->no->parent = new_node;
    }
    free(node1);
}
