#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

typedef double func_const_t;

typedef size_t (*hash_func_t) (char*, func_const_t, size_t);
typedef func_const_t (*gen_const_func_t) (void);

typedef struct list list_t;

struct list
{
    char str[STR_MAX];
    list_t *next;
};


typedef struct
{
    list_t **table;
    size_t size;
    func_const_t func_const;
    hash_func_t hash_func;
}hash_table_t;

int create_table(hash_table_t *table, size_t size, hash_func_t h_func, gen_const_func_t gen_const);
void free_table(hash_table_t *table);
func_const_t gen_f0_t1();
size_t func_mlt(char elem[STR_MAX], func_const_t c, size_t size);
size_t func_mod(char elem[STR_MAX], func_const_t c, size_t size);
int add_to_table(hash_table_t *table, char elem[STR_MAX]);
int fread_table(char *file_name, hash_table_t *table);
void delete_from_table(hash_table_t *table, char elem[STR_MAX]);
double count_avg_comparisons(hash_table_t table);
int restruct_table(hash_table_t *table, hash_func_t h_func, gen_const_func_t gen_const);
void search_in_table(hash_table_t table, char elem[STR_MAX], size_t *comparisons, int *find);
void write_table(FILE *dst, hash_table_t table);

#endif //HASH_TABLE_H
