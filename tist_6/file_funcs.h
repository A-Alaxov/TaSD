#ifndef ELEM_FUNCS_H
#define ELEM_FUNCS_H

#include <stdio.h>
#include "header.h"

void fwrite_elem(FILE *dst, char src[STR_MAX]);
int fread_elem(FILE *src, char *dst);
int add_to_file(char *file_name, char elem[STR_MAX]);
int delete_from_file(char *file_name, char key[STR_MAX]);
int search_in_file(char *file_name, char elem[STR_MAX], size_t *comparisons, int *find);
int fwrite_file(FILE *dst, char *file_name);

#endif // ELEM_FUNCS_H
