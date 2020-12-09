#include "header.h"

void list_free(struct list *head)
{
    struct list *toto = head, *temp = toto;

    while (toto)
    {
        temp = toto->next;
        free(toto->value);
        free(toto);
        toto = temp;
    }
}

int list_fifo_free(struct list_fifo *list_queue)
{
    if (list_queue->pout)
    {
        list_free(list_queue->pout);
    }
    list_queue->pin = NULL;
    list_queue->pout = NULL;
    list_queue->len = 0;
    return OK;
}

struct list* list_get(struct list *head, size_t size, void *value)
{
    struct list *temp = head->next;
    if ((head->value) && (value))
        memcpy(value, head->value, size);
    return temp;
}

int list_fifo_get(struct list_fifo *list_queue, void *value)
{
    if (list_queue->len < 1)
    {
        return EMPTY_LIST_LIFO;
    }
    list_queue->pout = list_get(list_queue->pout, list_queue->size, value);

    if (!list_queue->pout)
    {
        list_queue->pin = list_queue->pout;
    }

    list_queue->len--;
    return OK;
}

struct list* list_get_adress(struct list *head, void **value)
{
    struct list *temp = head->next;
    *value = head;
    return temp;
}

int list_fifo_get_adress(struct list_fifo *list_queue, void **value)
{
    if (list_queue->len < 1)
    {
        return EMPTY_LIST_LIFO;
    }
    list_queue->pout = list_get_adress(list_queue->pout, value);

    if (!list_queue->pout)
    {
        list_queue->pin = list_queue->pout;
    }

    list_queue->len--;
    return OK;
}

struct list* list_delete(struct list *head, size_t size, void *value)
{
    struct list *temp = head->next;
    if ((head->value) && (value))
    {
        memcpy(value, head->value, size);
    }

    free(head->value);
    free(head);
    return temp;
}

int list_fifo_delete(struct list_fifo *list_queue, void *value, struct list **used_ptr)
{
    struct list *temp;
    if (list_queue->len < 1)
    {
        return EMPTY_LIST_LIFO;
    }

    if (used_ptr)
    {
        temp = node_create(&list_queue->pout, sizeof(void*));
        *used_ptr = list_add_begin(*used_ptr, temp);
    }

    list_queue->pout = list_delete(list_queue->pout, list_queue->size, value);

    if (!list_queue->pout)
    {
        list_queue->pin = list_queue->pout;
    }

    list_queue->len--;
    return OK;
}

int vect_fifo_free(struct vect_fifo *vect_queue)
{
    if (vect_queue->q1)
    {
        free(vect_queue->q1);
    }
    vect_queue->q1 = NULL;
    vect_queue->qm = NULL;
    vect_queue->pin = NULL;
    vect_queue->pout = NULL;
    vect_queue->len = 0;
    return OK;
}

int vect_fifo_get(struct vect_fifo *vect_queue, void *value)
{
    if (vect_queue->len < 1)
    {
        return EMPTY_VECT_LIFO;
    }

    if (value)
        memcpy(value, vect_queue->pout, vect_queue->size);

    vect_queue->pout = (char*)vect_queue->pout + vect_queue->size;
    if (vect_queue->pout == vect_queue->qm)
        vect_queue->pout = vect_queue->q1;

    vect_queue->len--;
    return OK;
}
