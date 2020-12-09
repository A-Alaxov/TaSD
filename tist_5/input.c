#include "header.h"

struct list* node_create(void *value, size_t size)
{
    struct list *node = malloc(sizeof(struct list));

    if (!node)
    {
        return NULL;
    }

    if (value)
    {
        node->value = malloc(size);
        memcpy(node->value, value, size);
    }
    else
    {
        node->value = NULL;
    }
    node->next = NULL;
    return node;
}

struct list* list_add_begin(struct list *head, struct list *node)
{
    node->next = head;
    return node;
}

struct list* list_add(struct list *head, struct list *node)
{
    if (!head)
        return node;

    node_t *cur = head;
    while (cur->next)
        cur = cur->next;

    cur->next = node;
    cur = cur->next;
    return cur;
}

int list_fifo_add(struct list_fifo *list_queue, void *value, struct list **used_ptr)
{
    struct list *node, *cur;
    node = node_create(value, list_queue->size);
    if (!node)
    {
        return MEM_ALLOC_ERROR;
    }
    list_queue->len++;
    /*
    if (list_stack->len > STACK_MAX)
    {
        return LIST_OVERFLOW;
    }
    */
    list_queue->pin = list_add(list_queue->pin, node);

    if (used_ptr)
    {
        cur = *used_ptr;
        while ((cur) && (cur->next))
        {
            if (list_queue->pin == *(void**)cur->next->value)
                cur->next = list_delete(cur->next, sizeof(void*), NULL);
            cur =cur->next;
        }

        if ((*used_ptr) && (list_queue->pin == *(void**)(*used_ptr)->value))
            *used_ptr = list_delete(*used_ptr, sizeof(void*), NULL);
    }

    if (!list_queue->pout)
    {
        list_queue->pout = list_queue->pin;
    }
    return OK;
}

int list_fifo_create(struct list_fifo *list_queue, size_t size)
{
    list_queue->pin = NULL;
    list_queue->pout = NULL;
    list_queue->len = 0;
    list_queue->size = size;
    return OK;
}

int vect_fifo_add(struct vect_fifo *vect_queue, void *value)
{
    vect_queue->len++;
    if (vect_queue->len > STACK_MAX)
    {
        return VECT_OVERFLOW;
    }

    if (value)
        memcpy(vect_queue->pin, value, vect_queue->size);

    vect_queue->pin = (char*)vect_queue->pin + vect_queue->size;
    if (vect_queue->pin == vect_queue->qm)
        vect_queue->pin = vect_queue->q1;

    return OK;
}

int vect_fifo_create(struct vect_fifo *vect_queue, size_t end, size_t size)
{
    vect_queue->q1 = malloc(end * size);
    if (!vect_queue->q1)
    {
        return MEM_ALLOC_ERROR;
    }
    vect_queue->len = 0;
    vect_queue->qm = (char*)vect_queue->q1 + end * size;
    vect_queue->pin = vect_queue->q1;
    vect_queue->pout = vect_queue->q1;
    vect_queue->size = size;
    return OK;
}
