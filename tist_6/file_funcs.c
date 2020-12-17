#include "ddp_tree.h"
#include "header.h"
#include "file_funcs.h"

int fread_elem(FILE *src, char *dst)
{
    if (fscanf(src, "%s", dst) != 1)
        return READ_ER;

    return EXIT_SUCCESS;
}

void fwrite_elem(FILE *dst, char src[STR_MAX])
{
    fprintf(dst, " %s", src);
}

int fwrite_file(FILE *dst, char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ER;

    char el[STR_MAX];
    while (!fread_elem(f, el))
    {
        fwrite_elem(dst, el);
        fprintf(dst, "\n");
    }

    fclose(f);

    return EXIT_SUCCESS;
}
int add_to_file(char *file_name, char elem[STR_MAX])
{
    FILE *f = fopen(file_name, "a+");
    if (!f)
        return OPEN_ER;

    char el[STR_MAX];
    while (!fread_elem(f, el))
    {

    }

    if (feof(f))
        fwrite_elem(f, elem);

    fclose(f);

    return EXIT_SUCCESS;
}

int search_in_file(char *file_name, char elem[STR_MAX], size_t *comparisons, int *find)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_ER;

    *comparisons = 0;
    *find = 0;
    char el[STR_MAX];
    while (!fread_elem(f, el) && !(*find))
    {
        *comparisons += 1;
        if (!strcmp(el, elem))
            *find = 1;
    }

    fclose(f);

    return EXIT_SUCCESS;
}

int delete_from_file(char *file_name, char key[STR_MAX])
{
    FILE *f = fopen(file_name, "r");
    if (!f)
      return OPEN_ER;

    FILE *temp = fopen("temp.txt", "w");
    if (!temp)
    {
        fclose(f);
        return OPEN_ER;
    }

    char buf[STR_MAX];
    while (fscanf(f, "%s", buf) == 1)
    {
        if (strcmp(buf, key))
            fprintf(temp, "%s\n", buf);
    }

    fclose(f);
    fclose(temp);

    remove(file_name);
    rename("temp.txt", file_name);

    return EXIT_SUCCESS;
}
