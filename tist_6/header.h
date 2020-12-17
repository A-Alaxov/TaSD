#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define STACK_MAX 1000
#define STR_MAX 500
#define EPS 1e-8

#define INCORRECT_INPUT -1
#define MEM_ALLOC_ERROR -2
#define INCORRECT_OPTION -3
#define INCORRECT_FILE_NAME -4
#define READ_ER 1
#define OPEN_ER 2
#define MEM_ER 3
#define TABLE_OVR 4
#define OK 0

typedef struct node node_t;

struct node
{
    char data[STR_MAX];
    node_t *left;
    node_t *right;
};

typedef struct balance_node balance_node_t;

struct balance_node
{
    char data[STR_MAX];
    unsigned char height;
    balance_node_t *right;
    balance_node_t *left;
};

#endif // ERRORS_H
