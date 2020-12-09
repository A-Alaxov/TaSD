#include "header.h"

int print_list_int(struct list_fifo *temp)
{
    int rc = OK, elem;
    rc = list_fifo_get(temp, &elem);
    if (!rc)
    {
        printf("%d ", elem);
    }
    return rc;
}

int print_list_ptr(struct list_fifo *temp)
{
    int rc = OK;
    void *elem;
    rc = list_fifo_get_adress(temp, &elem);
    if (!rc)
    {
        printf("%p ", elem);
    }
    return rc;
}

int print_vect_int(struct vect_fifo *temp)
{
    int rc = OK, elem;
    rc = vect_fifo_get(temp, &elem);
    if (!rc)
    {
        printf("%d ", elem);
    }
    return rc;
}

int list_fifo_print(struct list_fifo list_queue, struct list *used_ptr, int (*f)(struct list_fifo *temp))
{
    int rc = OK;
    struct list_fifo temp;
    temp.pout = list_queue.pout;
    temp.len = list_queue.len;
    temp.size = list_queue.size;
    printf("\nValues of stack: ");
    while ((temp.pout) && (!rc))
    {
        rc = f(&temp);
    }

    temp.pout = list_queue.pout;
    temp.len = list_queue.len;
    temp.size = list_queue.size;
    printf("\nAdresses of elements: ");
    while ((temp.pout) && (!rc))
    {
        rc = print_list_ptr(&temp);
    }

    printf("\nFree adresses: ");
    while (used_ptr)
    {
        printf("%p ", *(void**)used_ptr->value);
        used_ptr = used_ptr->next;
    }
    printf("\n");
    return rc;
}

int vect_fifo_print(struct vect_fifo vect_queue, int (*f)(struct vect_fifo *temp))
{
    int rc = OK;
    struct vect_fifo temp;
    temp.q1 = vect_queue.q1;
    temp.qm = vect_queue.qm;
    temp.pin = vect_queue.pin;
    temp.pout = vect_queue.pout;
    temp.len = vect_queue.len;
    temp.size = vect_queue.size;
    printf("\nValues of stack: ");
    for (size_t i = 0; i < vect_queue.len; i++)
    {
        rc = f(&temp);
    }
    printf("\n");
    return rc;
}
