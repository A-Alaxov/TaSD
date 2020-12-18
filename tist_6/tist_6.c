#include "ddp_tree.h"
#include "avl_tree.h"
#include "file_funcs.h"
#include "header.h"
#include "hash_table.h"
#include "statistic.h"

#define VIZ_BIN_TREE "viz/binary_tree.gv"
#define VIZ_BAL_TREE "viz/balance_tree.gv"

int main()
{
    setbuf(stdout, NULL);
    int rc = OK;
    char elem[STR_MAX];
    size_t size;

    char f_name[STR_MAX] = "test.txt";

    printf("This program contains addition, deletion and search in binary tree, balance tree, file and hash table\n"
           "Also program compares this types of data by time and used memory\n\n");

    printf("Input name of file with data: ");

    if (!scanf("%s", f_name))
    {
        printf("Incorrect name of file\n");
        return INCORRECT_FILE_NAME;
    }

    int input;
    printf("\nInput 1 to see binary tree operations\n"
           "Input 2 to see balance tree operations\n"
           "Input 3 to see file operations\n"
           "Input 4 to see hash table operations\n"
           "Input 5 to compare searches\n"
           "Input 0 for exit\n");
    if (!scanf("%d", &input))
    {
        rc = INCORRECT_OPTION;
    }

    while ((input) && (!rc))
    {
        if (input == 1)
        {
            int input_in;
            node_t *root = NULL;
            printf("\nInput 1 to read binary tree from file\n"
                   "Input 2 to add element to binary tree\n"
                   "Input 3 to delete from binary tree\n"
                   "Input 4 to search in binary tree\n"
                   "Input 5 to print binary tree\n"
                   "Input 0 for exit\n");
            if (!scanf("%d", &input_in))
            {
                rc = INCORRECT_OPTION;
            }
            while ((input_in) && (!rc))
            {
                if (input_in == 1)
                {
                    rc = fread_tree(f_name, &root);
                }
                else if (input_in == 2)
                {
                    printf("input element: ");
                    rc = fread_elem(stdin, elem);
                    if (!rc)
                    {
                        rc = add_to_tree(&root, elem);
                    }
                }
                else if (input_in == 3)
                {
                    printf("input element: ");
                    rc = fread_elem(stdin, elem);
                    if (!rc)
                    {
                        delete_from_tree(&root, elem);
                    }
                }
                else if (input_in == 4)
                {
                    printf("input element: ");
                    if (fread_elem(stdin, elem))
                    {
                        printf("Incorrect elemen\n");
                        continue;
                    }
                    size_t comparisons = 0;
                    int found;
                    search_in_tree(root, elem, &comparisons, &found);
                    if (found)
                        printf("Element %s was found with %zu comparisons\n", elem, comparisons);
                    else
                        printf("Not found.\n");
                }
                else if (input_in == 5)
                {
                    export_to_dot(root, VIZ_BIN_TREE, "binary_tree");
                    system("dot -Tpng viz/binary_tree.gv -o viz/binary_tree.png && mspaint viz\\binary_tree.png");
                }
                else
                {
                    printf("\nYou should choose one of the listed options\n");
                }

                if (!rc)
                {
                    printf("\nInput 1 to read binary tree from file\n"
                           "Input 2 to add element to binary tree\n"
                           "Input 3 to delete from binary tree\n"
                           "Input 4 to search in binary tree\n"
                           "Input 5 to print binary tree\n"
                           "Input 0 for exit\n");
                    if (!scanf("%d", &input_in))
                    {
                        rc = INCORRECT_OPTION;
                    }
                }
            }

            free_tree(root);
        }
        else if (input == 2)
        {
            int input_in;
            balance_node_t *balance_node = NULL;
            printf("\nInput 1 to read balance tree from file\n"
                   "Input 2 to add element to balance tree\n"
                   "Input 3 to delete from balance tree\n"
                   "Input 4 to search in balance tree\n"
                   "Input 5 to print balance tree\n"
                   "Input 0 for exit\n");
            if (!scanf("%d", &input_in))
            {
                rc = INCORRECT_OPTION;
            }
            while ((input_in) && (!rc))
            {
                if (input_in == 1)
                {
                    rc = fread_btree(f_name, &balance_node);
                }
                else if (input_in == 2)
                {
                    printf("input element: ");
                    rc = fread_elem(stdin, elem);
                    if (!rc)
                    {
                        rc = add_to_btree(&balance_node, elem);
                    }
                }
                else if (input_in == 3)
                {
                    printf("input element: ");
                    rc = fread_elem(stdin, elem);
                    if (!rc)
                    {
                        delete_from_btree(&balance_node, elem);
                    }
                }
                else if (input_in == 4)
                {
                    printf("input element: ");
                    if (fread_elem(stdin, elem))
                    {
                        printf("Incorrect elemen\n");
                        continue;
                    }
                    size_t comparisons = 0;
                    int found;
                    search_in_btree(balance_node, elem, &comparisons, &found);
                    if (found)
                        printf("Element %s was found with %zu comparisons\n", elem, comparisons);
                    else
                        printf("Not found.\n");
                }
                else if (input_in == 5)
                {
                    bexport_to_dot(balance_node, VIZ_BAL_TREE, "balance_tree");
                    system("dot -Tpng viz/balance_tree.gv -o ./viz/balance_tree.png && mspaint viz\\balance_tree.png");
                }
                else
                {
                    printf("\nYou should choose one of the listed options\n");
                }

                if (!rc)
                {
                    printf("\nInput 1 to read balance tree from file\n"
                           "Input 2 to add element to balance tree\n"
                           "Input 3 to delete from balance tree\n"
                           "Input 4 to search in balance tree\n"
                           "Input 5 to print balance tree\n"
                           "Input 0 for exit\n");
                    if (!scanf("%d", &input_in))
                    {
                        rc = INCORRECT_OPTION;
                    }
                }
            }

            free_btree(balance_node);
        }
        else if (input == 3)
        {
            int input_in;
            printf("\nInput 1 to add element to file\n"
                   "Input 2 to delete from file\n"
                   "Input 3 to search in file\n"
                   "Input 4 to print file\n"
                   "Input 0 for exit\n");
            if (!scanf("%d", &input_in))
            {
                rc = INCORRECT_OPTION;
            }
            while ((input_in) && (!rc))
            {
                if (input_in == 1)
                {
                    printf("input element: ");
                    rc = fread_elem(stdin, elem);
                    if (!rc)
                    {
                        rc = add_to_file(f_name, elem);
                    }
                }
                else if (input_in == 2)
                {
                    printf("input element: ");
                    rc = fread_elem(stdin, elem);
                    if (!rc)
                    {
                        delete_from_file(f_name, elem);
                    }
                }
                else if (input_in == 3)
                {
                    printf("input element: ");
                    if (fread_elem(stdin, elem))
                    {
                        printf("Incorrect elemen\n");
                        continue;
                    }
                    size_t comparisons = 0;
                    int found;
                    search_in_file(f_name, elem, &comparisons, &found);
                    if (found)
                        printf("Element %s was found with %zu comparisons\n", elem, comparisons);
                    else
                        printf("Not found.\n");
                }
                else if (input_in == 4)
                {
                    rc = fwrite_file(stdout, f_name);
                }
                else
                {
                    printf("\nYou should choose one of the listed options\n");
                }

                if (!rc)
                {
                    printf("\nInput 1 to add element to file\n"
                           "Input 2 to delete from file\n"
                           "Input 3 to search in file\n"
                           "Input 4 to print file\n"
                           "Input 0 for exit\n");
                    if (!scanf("%d", &input_in))
                    {
                        rc = INCORRECT_OPTION;
                    }
                }
            }
        }
        else if (input == 4)
        {
            int input_in;
            printf("Input table size: \n");
            if (scanf("%zu", &size) != 1)
                return EXIT_FAILURE;
            printf("Input table max avg comparisons: \n");
            double max_avg_cmp;
            if (scanf("%lf", &max_avg_cmp) != 1)
                return EXIT_FAILURE;
            hash_table_t table;
            rc = create_table(&table, size, func_mod, NULL);
            if (rc)
            {
                printf("can't create table\n");
                return rc;
            }
            printf("\nInput 1 to read hash table from file\n"
                   "Input 2 to add element to hash table\n"
                   "Input 3 to delete from hash table\n"
                   "Input 4 to search in hash table\n"
                   "Input 5 to count avg comparisons\n"
                   "Input 6 to print hash table\n"
                   "Input 0 for exit\n");
            if (!scanf("%d", &input_in))
            {
                rc = INCORRECT_OPTION;
            }
            while ((input_in) && (!rc))
            {
                if (input_in == 1)
                {
                    rc = fread_table(f_name, &table);
                    while ((!rc) && (count_avg_comparisons(table) > max_avg_cmp))
                    {
                        rc = restruct_table(&table, func_mod, NULL);
                    }
                }
                else if (input_in == 2)
                {
                    printf("input element: ");
                    rc = fread_elem(stdin, elem);
                    if (!rc)
                    {
                        rc = add_to_table(&table, elem);
                    }
                    while ((!rc) && (count_avg_comparisons(table) > max_avg_cmp))
                    {
                        rc = restruct_table(&table, func_mod, NULL);
                    }
                }
                else if (input_in == 3)
                {
                    printf("input element: ");
                    rc = fread_elem(stdin, elem);
                    if (!rc)
                    {
                        delete_from_table(&table, elem);
                    }
                }
                else if (input_in == 4)
                {
                    printf("input element: ");
                    if (fread_elem(stdin, elem))
                    {
                        printf("Incorrect elemen\n");
                        continue;
                    }
                    size_t comparisons = 0;
                    int found;
                    search_in_table(table, elem, &comparisons, &found);
                    if (found)
                        printf("Element %s was found with %zu comparisons\n", elem, comparisons);
                    else
                        printf("Not found.\n");
                }
                else if (input_in == 5)
                {
                    printf("average comparosons - %lf\n", count_avg_comparisons(table));
                }
                else if (input_in == 6)
                {
                    write_table(stdout, table);
                }
                else
                {
                    printf("\nYou should choose one of the listed options\n");
                }

                if (!rc)
                {
                    printf("\nInput 1 to read hash table from file\n"
                           "Input 2 to add element to hash table\n"
                           "Input 3 to delete from hash table\n"
                           "Input 4 to search in hash table\n"
                           "Input 5 to count avg comparisons\n"
                           "Input 6 to print hash table\n"
                           "Input 0 for exit\n");
                    if (!scanf("%d", &input_in))
                    {
                        rc = INCORRECT_OPTION;
                    }
                }
            }

            free_table(&table);
        }
        else if (input == 5)
        {
            all_stat();
        }
        else
        {
            printf("\nYou should choose one of the listed options\n");
        }

        if (!rc)
        {
            printf("\nInput 1 to see binary tree operations\n"
                   "Input 2 to see balance tree operations\n"
                   "Input 3 to see file operations\n"
                   "Input 4 to see hash table operations\n"
                   "Input 5 to compare searches\n"
                   "Input 0 for exit\n");
            if (!scanf("%d", &input))
            {
                rc = INCORRECT_OPTION;
            }
        }
    }

    if ((!input) && (!rc))
    {
        printf("\nEnd of work");
    }

    if (rc == INCORRECT_INPUT)
        printf("\nIncorrect input\n");
    else if (rc == MEM_ALLOC_ERROR)
        printf("\nMemory allocation error\n");
    else if (rc == INCORRECT_OPTION)
        printf("\nIncorrect option\n");
    else if (rc == INCORRECT_FILE_NAME)
        printf("\nIncorrect file name\n");
    else if (rc == READ_ER)
        printf("\nIncorrect file name\n");
    else if (rc == OPEN_ER)
        printf("\nIncorrect file name\n");
    else if (rc == MEM_ER)
        printf("\nIncorrect file name\n");
    else if (rc == TABLE_OVR)
        printf("\nIncorrect file name\n");

    return rc;
}
