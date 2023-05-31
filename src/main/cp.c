#include <assert.h>
#include <stdlib.h>

#include "command.h"
#include "constants.h"
#include "tree_dir_core.h"

static void copy_content_of(node *, node *);

int cp(const command *cmd)
{
    if (!handle_number_of_args(2, cmd->args_number))
    {
        return INVALID_NUMBER_OF_ARGS;
    }
    node *node_to_copy = search_node_in_tree(current_node, cmd->args[0]);

    if (node_to_copy == NULL)
    {
        write_result_command("Invalid path to copy.");
        return INVALID_PATH;
    }

    node *node_to_append =
        search_node_in_tree_with_node_creation(current_node, cmd->args[1], node_to_copy->is_directory);

    if (node_to_append == NULL)
    {
        write_result_command("Invalid path to create a copy.");
        return INVALID_PATH;
    }

    if (!is_valid_name_node(node_to_append->name))
    {
        write_result_command(
            "Invalid name : the name of an element can neither be empty nor contain special characters.");
        destroy_node(node_to_append);
        return INVALID_NAME;
    }

    if (is_node_inside(node_to_append->parent, node_to_copy))
    {
        write_result_command("An element cannot be copied inside a directory contained in the copy.");
        destroy_node(node_to_append);
        return INVALID_SELECTION;
    }

    int append_error_value = append_child_to_node(node_to_append->parent, node_to_append);

    if (append_error_value == INVALID_NAME)
    {
        write_result_command("Invalid name : an element with the same name already exists.");
        destroy_node(node_to_append);
        return INVALID_NAME;
    }

    if (append_error_value != SUCCESS)
    {
        write_result_command("Error while copying the element.");
        destroy_node(node_to_append);
        return FATAL_ERROR;
    }

    copy_content_of(node_to_append, node_to_copy);

    return SUCCESS;
}

/*
Copy all contents of node1 inside node2

The node1 should be empty, that means that it should not have any offspring,
to avoid the problem of same name in append_child_to_node.
*/
static void copy_content_of(node *node1, node *node2)
{
    if (!node1->is_directory || !node2->is_directory)
    {
        return;
    }
    for (liste_node *lst = node2->children; lst != NULL; lst = lst->succ)
    {
        node *node_to_append = create_node(lst->no->is_directory, lst->no->name, node1);
        append_child_to_node(node1, node_to_append);

        copy_content_of(node_to_append, lst->no);
    }
}
