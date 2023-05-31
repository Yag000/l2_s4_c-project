#ifndef TREE_DIR_CORE_H
#define TREE_DIR_CORE_H

#include <stdbool.h>

#define MAX_LENGTH_NOM 100

typedef struct node
{
    bool is_directory;
    char nom[MAX_LENGTH_NOM];
    struct node *parent;
    struct node *racine;
    struct liste_node *fils;
} node;

typedef struct liste_node
{
    struct node *no;
    struct liste_node *succ;
} liste_node;

extern node *current_node;

node *create_node(bool, const char *, node *);
node *create_node_with_fils(bool, const char *, node *, liste_node *);
bool is_valid_name_node(const char *);
node *create_root_node();
void destroy_node(node *);
bool are_nodes_equal(const node *, const node *);
bool is_root_node(const node *);
bool is_fils_of_node_empty(const node *);
bool contains_node(node *, node *);
unsigned get_number_of_fils(node *);
node *get_a_fils_of_node(node *, const char *);
int append_a_fils_to_node(node *, node *);
int remove_a_node_from_fils(node *, node *);
int remove_a_fils_of_node(node *, const char *);

liste_node *create_liste_node(node *);
void destroy_liste_node(liste_node *);
bool contains_liste_node(liste_node *, node *);
unsigned size_liste_node(liste_node *);
node *get_a_node_in_liste_node(liste_node *, const char *);
int append_liste_node(liste_node *, node *);
liste_node *remove_liste_node(liste_node *, node *);

node *search_node_in_tree(node *, char *);
bool is_node_inside(const node *, const node *);
void destroy_tree();

unsigned get_longest_name_length_of_node_fils(const node *);
char *get_absolute_path_of_node(const node *);
node *search_node_in_tree(node *, char *);
node *search_node_in_tree_with_node_creation(node *, char *, bool);

void move_fils_of_node_to_new_node(node *, node *);

#endif
