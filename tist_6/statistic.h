#ifndef STATISTIC_H
#define STATISTIC_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "file_funcs.h"
#include "ddp_tree.h"
#include "avl_tree.h"
#include "hash_table.h"

#define FILE_NAME "test.txt"

#define ITERATIONS 1000

struct tmp_str
{
    char str[STR_MAX];
};

int all_stat();

#endif //STATISTIC_H
