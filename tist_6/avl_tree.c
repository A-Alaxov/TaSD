#include "avl_tree.h"
#include "header.h"
#include "file_funcs.h"

balance_node_t *create_bnode()
{
    balance_node_t *node = malloc(sizeof(balance_node_t));

    if (node)
    {
        node->height = 0;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

unsigned char height(balance_node_t *node)
{
    return node ? node->height : 0;
}

int bfactor(balance_node_t *node)
{
    return height(node->right) - height(node->left);
}

void fix_height(balance_node_t *node)
{
    unsigned char hl = height(node->left);
    unsigned char hr = height(node->right);
    node->height = (hl > hr ? hl : hr) + 1;
}

void bto_dot(balance_node_t *node, void *file)
{
    if (node->left)
        fprintf((FILE *) file, "%s -> %s\n", node->data, node->left->data);
    if (node->right)
        fprintf((FILE *) file, "%s -> %s\n", node->data, node->right->data);

    if (!node->left && !node->right)
        fprintf((FILE *) file, "%s\n", node->data);
}

void bpost_apply(balance_node_t *root, void (*func)(void *))
{
    if (!root)
        return;
    
    bpost_apply(root->left, func);
    bpost_apply(root->right, func);

    func(root);
}

void bpre_apply(balance_node_t *root, void (*func)(balance_node_t *, void *), void *param)
{
    if (!root)
        return;

    func(root, param);
    
    bpre_apply(root->left, func, param);
    bpre_apply(root->right, func, param);
}

void free_btree(balance_node_t *root)
{
    bpost_apply(root, free);
}

balance_node_t *rotate_left(balance_node_t *q)
{
    balance_node_t *p = q->right;
    q->right = p->left;
    p->left = q;
    fix_height(q);
    fix_height(p);
    return p;
}

balance_node_t *rotate_right(balance_node_t *p)
{
    balance_node_t *q = p->left;
    p->left = q->right;
    q->right = p;
    fix_height(p);
    fix_height(q);
    return q;
}

balance_node_t *balance(balance_node_t *node)
{
    fix_height(node);
    if (bfactor(node) == 2)
    {
        if (bfactor(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    if (bfactor(node) == -2)
    {
        if (bfactor(node->left) > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    return node;
}

int add_to_btree(balance_node_t **root, char elem[STR_MAX])
{
    int rc = EXIT_SUCCESS;
    if (!(*root))
    {
        balance_node_t *node = create_bnode();
        if (!node)
            return MEM_ER;
        strcpy(node->data, elem);
        *root = node;
    }
    else if (strcmp(elem, (*root)->data) > 0)
        rc = add_to_btree(&(*root)->right, elem);
    else if (strcmp(elem, (*root)->data) < 0)
        rc = add_to_btree(&(*root)->left, elem);
    
    *root = balance(*root);
    
    return rc;
}

char *find_btree_min(balance_node_t *root)
{
    if (!root->left)
        return root->data;
    
    return find_btree_min(root->left);
}

char *find_btree_max(balance_node_t *root)
{
    if (!root->right)
        return root->data;
    
    return find_btree_min(root->right);
}

void delete_from_btree(balance_node_t **root, char elem[STR_MAX])
{
    if (!(*root))
        return;
    else if (strcmp(elem, (*root)->data) > 0)
    {
        delete_from_btree(&(*root)->right, elem);
    }
    else if (strcmp(elem, (*root)->data) < 0)
    {
        delete_from_btree(&(*root)->left, elem);
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
            balance_node_t *node = *root;
            *root = (*root)->left;
            free(node);
            return;
        }
        else if (!(*root)->left && (*root)->right)
        {
            balance_node_t *node = *root;
            *root = (*root)->right;
            free(node);
            return;
        }
        else
        {
            char min[STR_MAX] = "";
            strcpy(min, find_btree_min((*root)->right));
            strcpy((*root)->data, min);
            delete_from_btree(&(*root)->right, min);
            return;
        }
    }

    *root = balance(*root);
}

int fread_btree(char *file_name, balance_node_t **root)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ER;
    
    char elem[STR_MAX];
    while (!fread_elem(f, elem))
    {
        int rc = add_to_btree(root, elem);
        if (rc)
        {
            fclose(f);
            return rc;
        }
    }

    fclose(f);
    
    return EXIT_SUCCESS;
}

int bexport_to_dot(balance_node_t *root, char *file_dst, char *tree_name)
{
    FILE *f = fopen(file_dst, "w");
    if (!f)
        return OPEN_ER;

    fprintf(f, "digraph %s {\n", tree_name);

    bpre_apply(root, bto_dot, f);

    fprintf(f, "}\n");

    fclose(f);

    return EXIT_SUCCESS;
}

void search_in_btree(balance_node_t *root, char elem[STR_MAX], size_t *comparisons, int *find)
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
