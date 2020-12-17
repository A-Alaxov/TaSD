#include <assert.h>
#include "header.h"
#include "statistic.h"

int gen_file(char *file_name, size_t elems, int file_type)
{
    FILE *f = fopen(file_name, "w");
    if (!f)
        return OPEN_ER;

    for (size_t i = 0; i < elems; i++)
    {
        long elem;
        if (file_type == 1)
            elem = i;
        else
        {
            elem = rand() % (elems * 10000);
            int sign = rand() % 2;
            if (sign)
                elem *= -1;
        }
        char str[STR_MAX];
        fwrite_elem(f, itoa(elem, str, 10));
        fprintf(f, "\n");
    }

    fclose(f);

    return EXIT_SUCCESS;
}

struct tmp_str *fread_in_array(char *file_name, size_t elems)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return NULL;
    
    struct tmp_str *ptr = malloc(elems * sizeof(struct tmp_str));

    size_t i = 0;
    while (!fread_elem(f, (ptr + i)->str))
    {
        i++;
    }

    fclose(f);

    return ptr;
}

int file_stat(char *file_name, size_t *memory, size_t elems,
              double *time_search, double *avg_cmp)
{
    struct tmp_str *a = fread_in_array(file_name, elems);
    if (!a)
        return EXIT_FAILURE;

    // search
    size_t cmp;
    int find;
    clock_t search = clock();
    for (size_t i = 0; i < ITERATIONS; i++)
    {
        for (size_t i = 0; i < elems; i++)
        {
            search_in_file(FILE_NAME, a[i].str, &cmp, &find);
        }
    }
    search = clock() - search;
    *time_search = ((double) search / CLOCKS_PER_SEC) / (ITERATIONS);

    // avg_cmp
    double cmp_sum = 0;
    for (size_t i = 0; i < elems; i++)
    {
        search_in_file(FILE_NAME, a[i].str, &cmp, &find);
        cmp_sum += cmp;
    }
    *avg_cmp = cmp_sum / elems;

    //memory
    *memory = 8;

    free(a);

    return EXIT_SUCCESS;
}

int binary_tree_stat(char *file_name, size_t *memory, size_t elems, \
                     double *time_search, double *avg_cmp)
{
    struct tmp_str *a = fread_in_array(file_name, elems);
    if (!a)
        return EXIT_FAILURE;

    // search
    size_t cmp;
    int find;
    node_t *root = NULL;
    fread_tree(file_name, &root);
    clock_t search = clock();
    for (size_t i = 0; i < ITERATIONS; i++)
    {
        for (size_t i = 0; i < elems; i++)
        {
            search_in_tree(root, a[i].str, &cmp, &find);
        }
    }
    search = clock() - search;
    *time_search = ((double) search / CLOCKS_PER_SEC) / (ITERATIONS);

    // avg_cmp
    double cmp_sum = 0;
    for (size_t i = 0; i < elems; i++)
    {
        search_in_tree(root, a[i].str, &cmp, &find);
        cmp_sum += cmp;
    }
    *avg_cmp = cmp_sum / elems;

    //memory
    *memory = elems * sizeof(node_t);

    free_tree(root);
    free(a);

    return EXIT_SUCCESS;
}

int balance_tree_stat(char *file_name, size_t *memory, size_t elems, \
                      double *time_search, double *avg_cmp)
{
    struct tmp_str *a = fread_in_array(file_name, elems);
    if (!a)
        return EXIT_FAILURE;

    // search
    size_t cmp;
    int find;
    balance_node_t *root = NULL;
    fread_btree(file_name, &root);
    clock_t search = clock();
    for (size_t i = 0; i < ITERATIONS; i++)
    {
        for (size_t i = 0; i < elems; i++)
        {
            search_in_btree(root, a[i].str, &cmp, &find);
        }
    }
    search = clock() - search;
    *time_search = ((double) search / CLOCKS_PER_SEC) / (ITERATIONS);

    // avg_cmp
    double cmp_sum = 0;
    for (size_t i = 0; i < elems; i++)
    {
        search_in_btree(root, a[i].str, &cmp, &find);
        cmp_sum += cmp;
    }
    *avg_cmp = cmp_sum / elems;

    //memory
    *memory = elems * sizeof(balance_node_t);

    free_btree(root);
    free(a);

    return EXIT_SUCCESS;
}

int find_best_hash_func(hash_table_t *table, char *file_name, size_t elems, double max_cmp)
{
    int rc = create_table(table, elems, func_mlt, gen_f0_t1);
    if (rc)
        return rc;
    rc = fread_table(file_name, table);
    if (rc)
        return rc;

    double avg_cmp = max_cmp;
    while ((count_avg_comparisons(*table) > max_cmp) && (avg_cmp != count_avg_comparisons(*table)))
    {
        avg_cmp = count_avg_comparisons(*table);
        int rc = restruct_table(table, func_mlt, gen_f0_t1);
        if (rc)
            return rc;
    }

    return EXIT_SUCCESS;
}

int hash_table_stat(char *file_name, double max_cmp, size_t *memory, size_t elems, \
                    double *time_search, double *avg_cmp)
{
    hash_table_t perfect_table;
    int rc = find_best_hash_func(&perfect_table, file_name, elems, max_cmp);
    assert(!rc);

    struct tmp_str *a = fread_in_array(file_name, elems);
    if (!a)
        return EXIT_FAILURE;

    // search
    size_t cmp;
    int find;
    clock_t search = clock();
    for (size_t i = 0; i < ITERATIONS; i++)
    {
        for (size_t i = 0; i < elems; i++)
        {
            search_in_table(perfect_table, a[i].str, &cmp, &find);
        }
    }
    search = clock() - search;
    *time_search = ((double) search / CLOCKS_PER_SEC) / (ITERATIONS);

    // avg_cmp
    double cmp_sum = 0;
    for (size_t i = 0; i < elems; i++)
    {
        search_in_table(perfect_table, a[i].str, &cmp, &find);
        cmp_sum += cmp;
    }
    *avg_cmp = cmp_sum / elems;

    //memory
    list_t *cur;
    *memory = perfect_table.size * sizeof(list_t*);
    for (size_t i = 0; i < perfect_table.size; i++)
    {
        cur = perfect_table.table[i];
        while (cur)
        {
            *memory += sizeof(node_t);
            cur = cur->next;
        }
    }

    free_table(&perfect_table);
    free(a);

    return EXIT_SUCCESS;
}

int all_stat()
{
    printf("1 - no random (1, 2, 3...)\n"
           "2 - random\n"
           "Choose file type: ");
    int file_type;
    scanf("%d", &file_type);

    printf("Input min elems, max elems, elems step: ");
    size_t min_elems, max_elems, elems_step;
    scanf("%zu %zu %zu", &min_elems, &max_elems, &elems_step);

    printf("Input max average comparisons in hash table: ");
    double max_cmp;
    scanf("%lf", &max_cmp);

    for (size_t elems = min_elems; elems <= max_elems; elems += elems_step)
    {
        int rc = gen_file(FILE_NAME, elems, file_type);
        if (rc)
        {
            printf("can't create file\n");
            return rc;
        }
        printf("elements - %zu\n", elems);
        printf("|  struct type | time search | avg comparisons |   memory |\n");

        size_t memory;
        double time_search, avg_cmp;

        // file
        rc = file_stat(FILE_NAME, &memory, elems, &time_search, &avg_cmp);
        if (rc)
        {
            printf("error.");
            return rc;
        }
        printf("| %12s | %10lfs | %15lf | %7zub |\n", "file", \
                time_search, avg_cmp, memory);

        // binary tree
        rc = binary_tree_stat(FILE_NAME, &memory, elems, &time_search, &avg_cmp);
        if (rc)
        {
            printf("error.");
            return rc;
        }
        printf("| %12s | %10lfs | %15lf | %7zub |\n", "binary tree", \
                time_search, avg_cmp, memory);

        //balance tree
        rc = balance_tree_stat(FILE_NAME, &memory, elems, &time_search, &avg_cmp);
        if (rc)
        {
            printf("error.");
            return rc;
        }
        printf("| %12s | %10lfs | %15lf | %7zub |\n", "balance tree", \
                time_search, avg_cmp, memory);

        //hash table
        rc = hash_table_stat(FILE_NAME, max_cmp, &memory, elems, &time_search, &avg_cmp);
        if (rc)
        {
            printf("error.");
            return rc;
        }
        printf("| %12s | %10lfs | %15lf | %7zub |\n", "hash table", \
                time_search, avg_cmp, memory);
    }

    return EXIT_SUCCESS;
}
