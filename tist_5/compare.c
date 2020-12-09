#include "header.h"

int compare()
{
    int rc = OK, elem = 1;
    size_t el_count = 500;
    struct list_fifo list_queue = { NULL, NULL, 0, sizeof(int) };
    struct vect_fifo vect_queue = { NULL, NULL, NULL, NULL, 0, sizeof(int) };

    rc = vect_fifo_create(&vect_queue, STACK_MAX, sizeof(int));

    clock_t start = clock();
    for (int i = 0; i < 10000; i++)
    {
        for (size_t j = 0; j < el_count; j++)
            vect_fifo_add(&vect_queue, &elem);
        for (size_t j = 0; j < el_count; j++)
            vect_fifo_get(&vect_queue, &elem);
        if (rc)
            return rc;
    }
    clock_t end = clock();
    printf("\nSpent time (in ms) by vect queue: %.4lf\n", (double)(end - start) / CLOCKS_PER_SEC / 10);
    printf("Memory (in bytes) spent at this queue: %d\n\n", (int)(sizeof(struct vect_fifo) + STACK_MAX * sizeof(int)));

    start = clock();
    for (int i = 0; i < 10000; i++)
    {
        for (size_t j = 0; j < el_count; j++)
            list_fifo_add(&list_queue, &elem, NULL);
        for (size_t j = 0; j < el_count; j++)
            list_fifo_delete(&list_queue, &elem, NULL);
        if (rc)
            return rc;
    }
    end = clock();

    printf("Spent time (in ms) by list queue: %.4lf\n", (double)(end - start) / CLOCKS_PER_SEC / 10);
    printf("Memory (in bytes) spent at this queue: %d\n", (int)(sizeof(struct list_fifo) + sizeof(struct list) * el_count + sizeof(int) * el_count));
    return OK;
}
