#include "ddp_tree.h"
#include "header.h"
#include "file_funcs.h"

node_t *create_node()
{
    node_t *node = malloc(sizeof(node_t));

    if (node)
    {
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

void post_apply(node_t *root, void (*func)(void *))
{
    if (!root)
        return;

    post_apply(root->left, func);
    post_apply(root->right, func);

    func(root);
}

void pre_apply(node_t *root, void (*func)(node_t *, void *), void *param)
{
    if (!root)
        return;

    func(root, param);

    pre_apply(root->left, func, param);
    pre_apply(root->right, func, param);
}

void free_tree(node_t *root)
{
    post_apply(root, free);
}

int add_to_tree(node_t **root, char elem[STR_MAX])
{
    if (!(*root))
    {
        node_t *node = create_node();
        if (!node)
            return MEM_ER;
        strcpy(node->data, elem);
        *root = node;
    }
    else if (strcmp(elem, (*root)->data) > 0)
        return add_to_tree(&(*root)->right, elem);
    else if (strcmp(elem, (*root)->data) < 0)
        return add_to_tree(&(*root)->left, elem);

    return EXIT_SUCCESS;
}

char *find_tree_min(node_t *root)
{
    if (!root->left)
        return root->data;

    return find_tree_min(root->left);
}

char *find_tree_max(node_t *root)
{
    if (!root->right)
        return root->data;

    return find_tree_min(root->right);
}

int fread_tree(char *file_name, node_t **root)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ER;

    char elem[STR_MAX];
    while (!fread_elem(f, elem))
    {
        int rc = add_to_tree(root, elem);
        if (rc)
        {
            fclose(f);
            return rc;
        }
    }

    fclose(f);

    return EXIT_SUCCESS;
}

void delete_from_tree(node_t **root, char elem[STR_MAX])
{
    if (!(*root))
        return;
    else if (strcmp(elem, (*root)->data) > 0)
    {
        delete_from_tree(&(*root)->right, elem);
        return;
    }
    else if (strcmp(elem, (*root)->data) < 0)
    {
        delete_from_tree(&(*root)->left, elem);
        return;
    }
    else
    {
        if (!(*root)->left && !(*root)->right)
        {
            free(*root);
            *root = NULL;
            return;
        }
        else if ((*root)->left && !(*root)->right)
        {
            node_t *node = *root;
            *root = (*root)->left;
            free(node);
        }
        else if (!(*root)->left && (*root)->right)
        {
            node_t *node = *root;
            *root = (*root)->right;
            free(node);
        }
        else
        {
            char min[STR_MAX] = "";
            strcpy(min, find_tree_min((*root)->right));
            strcpy((*root)->data, min);
            delete_from_tree(&(*root)->right, min);
        }
    }
}

void search_in_tree(node_t *root, char elem[STR_MAX], size_t *comparisons, int *find)
{
    *comparisons = 0;
    *find = 0;

    while (root && !(*find))
    {
        *comparisons += 1;
        if (!strcmp(root->data, elem))
            *find = 1;
        else if (strcmp(root->data, elem) > 0)
            root = root->left;
        else
            root = root->right;
    }
}

int export_to_dot(node_t *root, char *file_dst, char *tree_name)
{
    FILE *f = fopen(file_dst, "w");
    if (!f)
        return OPEN_ER;

    fprintf(f, "digraph %s {\n", tree_name);

    pre_apply(root, to_dot, f);

    fprintf(f, "}\n");

    fclose(f);

    return EXIT_SUCCESS;
}

void to_dot(node_t *node, void *file)
{
    if (node->left)
        fprintf((FILE *) file, "%s -> %s\n", node->data, node->left->data);
    if (node->right)
        fprintf((FILE *) file, "%s -> %s\n", node->data, node->right->data);

    if (!node->left && !node->right)
        fprintf((FILE *) file, "%s\n", node->data);
}
