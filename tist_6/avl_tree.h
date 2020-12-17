#ifndef AVL_TREE_FUNCS_H
#define AVL_TREE_FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include "ddp_tree.h"

void free_btree(balance_node_t *root);
int add_to_btree(balance_node_t **root, char elem[STR_MAX]);
int fread_btree(char *file_name, balance_node_t **root);
void delete_from_btree(balance_node_t **root, char elem[STR_MAX]);
int bexport_to_dot(balance_node_t *root, char *file_dst, char *tree_name);
void search_in_btree(balance_node_t *root, char elem[STR_MAX], size_t *comparisons, int *find);

balance_node_t *create_bnode();
unsigned char height(balance_node_t *node);
int bfactor(balance_node_t *node);
void fix_height(balance_node_t *node);
void bto_dot(balance_node_t *node, void *file);

#endif //AVL_TREE_FUNCS_H
