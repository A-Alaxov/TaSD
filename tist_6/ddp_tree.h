#ifndef DDP_TREE_FUNCS_H
#define DDP_TREE_FUNCS_H

#include "header.h"

node_t *create_node();
void free_tree(node_t *root);
int add_to_tree(node_t **root, char elem[STR_MAX]);
int fread_tree(char *file_name, node_t **root);
void delete_from_tree(node_t **root, char elem[STR_MAX]);
void search_in_tree(node_t *root, char elem[STR_MAX], size_t *comparisons, int *find);
int export_to_dot(node_t *root, char *file_dst, char *tree_name);
void to_dot(node_t *node, void *file);

#endif // DDP_TREE_FUNCS_H
