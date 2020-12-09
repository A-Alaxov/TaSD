#include "header.h"

int main()
{
    int rc = OK, elem;
    struct list_fifo list_queue = { NULL, NULL, 0, sizeof(int) };
    struct vect_fifo vect_queue = { NULL, NULL, NULL, NULL, 0, sizeof(int) };
    struct list *used_ptr = NULL;
    double t1_min, t1_max, t2_min, t2_max, t3_min, t3_max, t4_min, t4_max;

    rc = vect_fifo_create(&vect_queue, STACK_MAX, sizeof(int));
    if (rc)
    {
        printf("\nMemory allocation error\n");
        return rc;
    }

    printf("This program contains addition and deletion to queues realised by list and vect\n"
           "This program simulates the maintenance process by queues realised by list and vect\n"
           "Also program compares this two realisations by time and used memory\n"
           "\n");

    int input;
    printf("\nInput 1 to add element to vector queue\n"
           "Input 2 to add element to list queue\n"
           "Input 3 to delete element from vector queue\n"
           "Input 4 to delete element from list queue\n"
           "Input 5 to print condition of vector queue\n"
           "Input 6 to print condition of list queue\n"
           "Input 7 to simulate the maintenance process by list queue\n"
           "Input 8 to simulate the maintenance process by vect queue\n"
           "Input 9 to compare realisations\n"
           "Input 0 for exit\n");
    if (!scanf("%d", &input))
    {
        rc = INCORRECT_OPTION;
    }

    while ((input) && (!rc))
    {
        if (input == 1)
        {
            printf("\nEnter number: ");
            if (scanf("%d", &elem) != 1)
            {
                rc = INCORRECT_INPUT;
            }
            else
            {
                rc = vect_fifo_add(&vect_queue, &elem);
            }
        }
        else if (input == 2)
        {
            printf("\nEnter number: ");
            if (scanf("%d", &elem) != 1)
            {
                rc = INCORRECT_INPUT;
            }
            else
            {
                rc = list_fifo_add(&list_queue, &elem, &used_ptr);
            }
        }
        else if (input == 3)
        {
            rc = vect_fifo_get(&vect_queue, &elem);
            if (!rc)
            {
                printf("\nDeleted element: %d", elem);
            }
        }
        else if (input == 4)
        {
            rc = list_fifo_delete(&list_queue, &elem, &used_ptr);
            if (!rc)
            {
                printf("\nDeleted element: %d\n", elem);
            }
        }
        else if (input == 5)
        {
            rc = vect_fifo_print(vect_queue, print_vect_int);
        }
        else if (input == 6)
        {
            rc = list_fifo_print(list_queue, used_ptr, print_list_int);
        }
        else if (input == 7)
        {
            t1_min = 1;
            t1_max = 5;
            t2_min = 0;
            t2_max = 3;
            t3_min = 0;
            t3_max = 4;
            t4_min = 0;
            t4_max = 1;
            printf("T1 is from 1 to 5; T2 is from 0 to 3; T3 is from 0 to 4; T4 is from 0 to 1\n"
                   "If you want to change it, enter 1\n");
            if (!scanf("%d", &input))
            {
                rc = INCORRECT_OPTION;
            }
            if (input == 1)
            {
                printf("Please enter T1 min, T1 max, T2 min, T2 max, T3 min, T3 max, T4 min, T4 max\n");
                if (scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &t1_min, &t1_max, &t2_min, &t2_max, &t3_min, &t3_max, &t4_min, &t4_max) != 8)
                {
                    rc = INCORRECT_OPTION;
                }
            }
            if (!rc)
                list_operation(t1_min, t1_max, t2_min, t2_max, t3_min, t3_max, t4_min, t4_max);
        }
        else if (input == 8)
        {
            t1_min = 1;
            t1_max = 5;
            t2_min = 0;
            t2_max = 3;
            t3_min = 0;
            t3_max = 4;
            t4_min = 0;
            t4_max = 1;
            printf("T1 is from 1 to 5; T2 is from 0 to 3; T3 is from 0 to 4; T4 is from 0 to 1\n"
                   "If you want to change it, enter 1\n");
            if (!scanf("%d", &input))
            {
                rc = INCORRECT_OPTION;
            }
            if (input == 1)
            {
                printf("Please enter T1 min, T1 max, T2 min, T2 max, T3 min, T3 max, T4 min, T4 max\n");
                if (scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &t1_min, &t1_max, &t2_min, &t2_max, &t3_min, &t3_max, &t4_min, &t4_max) != 8)
                {
                    rc = INCORRECT_OPTION;
                }
                if ((rc) && ((t1_max < t1_min) || (t2_max < t2_min) || (t3_max < t3_min) || (t4_max < t4_min)))
                {
                    printf("max can't be bigger than min");
                    rc = INCORRECT_INPUT;
                }
            }
            if (!rc)
                vect_operation(t1_min, t1_max, t2_min, t2_max, t3_min, t3_max, t4_min, t4_max);
        }
        else if (input == 9)
        {
            compare();
        }
        else
        {
            printf("\nYou should choose one of the listed options\n");
        }

        if (!rc)
        {
            printf("\nInput 1 to add element to vector queue\n"
                   "Input 2 to add element to list queue\n"
                   "Input 3 to delete element from vector queue\n"
                   "Input 4 to delete element from list queue\n"
                   "Input 5 to print condition of vector queue\n"
                   "Input 6 to print condition of list queue\n"
                   "Input 7 to simulate the maintenance process by list queue\n"
                   "Input 8 to simulate the maintenance process by vect queue\n"
                   "Input 9 to compare realisations\n"
                   "Input 0 for exit\n");
            if (!scanf("%d", &input))
            {
                rc = INCORRECT_OPTION;
            }
        }
    }

    list_free(used_ptr);
    list_fifo_free(&list_queue);
    vect_fifo_free(&vect_queue);

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
    else if (rc == LIST_OVERFLOW)
        printf("\nList stack overflow\n");
    else if (rc == VECT_OVERFLOW)
        printf("\nVect stack overflow\n");
    else if (rc == EMPTY_LIST_LIFO)
        printf("\nDeletion from empty list stack\n");
    else if (rc == EMPTY_VECT_LIFO)
        printf("\nDeletion from empty vect stack\n");
    else if (rc == BAD_NUMBER)
        printf("\nError while getting number\n");
    else if (rc == BAD_SIGN)
        printf("\nError while getting sign\n");
    else if (rc == DEV_NULL)
        printf("\nDev by null\n");
    else if (rc == INCORRECT_STRING)
        printf("\nIncorrect string\n");

    return rc;
}
