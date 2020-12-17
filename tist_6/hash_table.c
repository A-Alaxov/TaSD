#include <math.h>
#include <string.h>
#include "hash_table.h"
#include "header.h"
#include "file_funcs.h"

int strsum(char str[STR_MAX])
{
    int i = 0, sum = 0;
    while (str[i] != '\0')
    {
        sum += str[i];
        i++;
    }
    return sum;
}

list_t* person_create(const char *name)
{
    list_t *pers = malloc(sizeof(list_t));

    if (pers)
    {
        strcpy(pers->str, name);
        pers->next = NULL;
    }

    return pers;
}

void list_free_all(list_t *head)
{
    list_t *next;

    for ( ; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

list_t* del_by_name(list_t *head, const char *name)
{
    list_t *cur, *prev = NULL;

    for (cur = head; cur; cur = cur->next)
    {
        if (strcmp(cur->str, name) == 0)
        {
            if (prev)
                prev->next = cur->next;
            else
                head = cur->next;
            free(cur);
            return  head;
        }
        prev = cur;
    }

    return NULL;
}

list_t* list_add_end(list_t *head, list_t *pers)
{
    list_t *cur = head;

    if (!head)
        return pers;

    for ( ; cur->next; cur = cur->next)
        ;

    cur->next = pers;

    return head;
}

int is_prime(size_t n)
{
    if (n <= 1)
        return 0;
    size_t i;
    i = 2;
    while (i < n / 2 + 1)
    {
        if (n % i == 0)
            return 0;
        i++;
    }
    return 1;
}

size_t find_next_prime(size_t n)
{
    size_t next = n + 2;
    for (; !is_prime(next); next++);
    return next;
}

int create_table(hash_table_t *table, size_t size, hash_func_t h_func, gen_const_func_t gen_const)
{
    table->table = calloc(size, sizeof(list_t*));
    if (!table->table)
        return MEM_ER;
    
    table->size = size;
    
    if (gen_const)
        table->func_const = gen_const();
    
    table->hash_func = h_func;

    return EXIT_SUCCESS;
}

void free_table(hash_table_t *table)
{
    for (size_t i = 0; i < table->size; i++)
        list_free_all(table->table[i]);
    free(table->table);
    memset(table, 0, sizeof(hash_table_t));
}

func_const_t gen_f0_t1()
{
    return (double) rand() / RAND_MAX;
}

size_t func_mlt(char elem[STR_MAX], func_const_t c, size_t size)
{
    double fraction_part;
    double int_part;
    fraction_part = modf(fabs(strsum(elem) * c), &int_part);

    return floor(fraction_part * size);
}

size_t func_mod(char elem[STR_MAX], func_const_t c, size_t size)
{
    return strsum(elem) % size;
}

size_t get_table_next(hash_table_t table, size_t cur_pos)
{
    if (cur_pos + 1 >= table.size)
        return 0;
    
    return cur_pos + 1;
}

size_t get_table_prev(hash_table_t table, size_t cur_pos)
{
    if (cur_pos == 0)
        return table.size - 1;
    
    return cur_pos - 1;
}

int add_to_table(hash_table_t *table, char elem[STR_MAX])
{
    size_t pos = table->hash_func(elem, table->func_const, table->size);
    list_t *node;

    node = person_create(elem);
    table->table[pos] = list_add_end(table->table[pos], node);

    return EXIT_SUCCESS;
}

int fread_table(char *file_name, hash_table_t *table)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ER;
    
    char elem[STR_MAX];
    while (!fread_elem(f, elem))
    {
        int rc = add_to_table(table, elem);
        if (rc)
        {
            fclose(f);
            return rc;
        }
    }

    fclose(f);
    
    return EXIT_SUCCESS;
}

void delete_from_table(hash_table_t *table, char elem[STR_MAX])
{
    size_t pos = table->hash_func(elem, table->func_const, table->size);
    table->table[pos] = del_by_name(table->table[pos], elem);
}

double count_avg_comparisons(hash_table_t table)
{
    size_t comparisons = 0, elems = 0;
    list_t *cur = NULL;
    for (size_t i = 0; i < table.size; i++)
    {
        cur = table.table[i];
        while (cur)
        {
            size_t cur_cmp;
            int find;
            search_in_table(table, cur->str, &cur_cmp, &find);
            comparisons += cur_cmp;
            elems++;
            cur = cur->next;
        }
    }
    
    return elems ? (double) comparisons / elems : 0;
}

int restruct_table(hash_table_t *table, hash_func_t h_func, gen_const_func_t gen_const)
{
    hash_table_t temp;
    list_t *cur = NULL;
    int rc = create_table(&temp, find_next_prime(table->size), h_func, gen_const);
    if (rc)
        return rc;
    
    for (size_t i = 0; i < table->size; i++)
    {
        cur = table->table[i];
        while (cur)
        {
            add_to_table(&temp, cur->str);
            cur = cur->next;
        }
    }
    
    free_table(table);

    *table = temp;

    return EXIT_SUCCESS;
}

void search_in_table(hash_table_t table, char elem[STR_MAX], size_t *comparisons, int *find)
{
    size_t pos = table.hash_func(elem, table.func_const, table.size);
    *comparisons = 0;
    *find = 0;
    list_t *cur = table.table[pos];
    while (cur && !*find)
    {
        *comparisons += 1;
        if (!strcmp(elem, cur->str))
            *find = 1;
        cur = cur->next;
    }
}

//not universal
void write_table(FILE *dst, hash_table_t table)
{
    list_t *cur = NULL;
    fprintf(dst, "| index | values\n");
    for (size_t i = 0; i < table.size; i++)
    {
        fprintf(dst, "|%7zu|", i);
        cur = table.table[i];
        while (cur)
        {
            fprintf(dst, " %s", cur->str);
            cur = cur->next;
        }
        fprintf(dst, "\n");
    }
}
