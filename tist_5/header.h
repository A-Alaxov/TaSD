#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define STACK_MAX 1000
#define STR_MAX 4000
#define EPS 1e-8

#define INCORRECT_INPUT -1
#define MEM_ALLOC_ERROR -2
#define INCORRECT_OPTION -3
#define LIST_OVERFLOW -4
#define VECT_OVERFLOW -5
#define EMPTY_LIST_LIFO -6
#define EMPTY_VECT_LIFO -7
#define BAD_NUMBER -8
#define END_OF_STRING -9
#define BAD_SIGN -10
#define DEV_NULL -11
#define INCORRECT_STRING -12
#define OK 0

struct vect_fifo
{
    void *q1, *qm, *pin, *pout;
    size_t len, size;
};

typedef struct list node_t;

struct list
{
    void *value;
    struct list *next;
};

struct list_fifo
{
    struct list *pin, *pout;
    size_t len, size;
};

int list_fifo_get(struct list_fifo *list_queue, void *value);

int vect_fifo_get(struct vect_fifo *vect_queue, void *value);

int list_fifo_add(struct list_fifo *list_queue, void *value, struct list **used_ptr);

int list_fifo_create(struct list_fifo *list_queue, size_t size);

int vect_fifo_add(struct vect_fifo *vect_queue, void *value);

int vect_fifo_create(struct vect_fifo *vect_queue, size_t end, size_t size);

int vect_fifo_free(struct vect_fifo *vect_queue);

int list_fifo_delete(struct list_fifo *list_queue, void *value, struct list **used_ptr);

struct list* list_delete(struct list *head, size_t size, void *value);

int list_fifo_free(struct list_fifo *list_queue);

int list_fifo_print(struct list_fifo list_queue, struct list *used_ptr, int (*f)(struct list_fifo *temp));

int print_list_int(struct list_fifo *temp);

int vect_fifo_print(struct vect_fifo vect_queue, int (*f)(struct vect_fifo *temp));

int print_vect_int(struct vect_fifo *temp);

struct list* node_create(void *value, size_t size);

struct list* list_add(struct list *head, struct list *node);

int list_fifo_get_adress(struct list_fifo *list_queue, void **value);

void list_free(struct list *head);

struct list* list_add_begin(struct list *head, struct list *node);

void list_operation(double t1_min, double t1_max, double t2_min, double t2_max, double t3_min, double t3_max, double t4_min, double t4_max);

void vect_operation(double t1_min, double t1_max, double t2_min, double t2_max, double t3_min, double t3_max, double t4_min, double t4_max);

int compare();

#endif // HEADER_H
