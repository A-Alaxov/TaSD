#include "header.h"

#define MAX_COUNT 1000

void list_operation(double t1_min, double t1_max, double t2_min, double t2_max, double t3_min, double t3_max, double t4_min, double t4_max)
{
    struct list_fifo type1 = { NULL, NULL, 0, sizeof(int) };
    struct list_fifo type2 = { NULL, NULL, 0, sizeof(int) };
    struct list_fifo type1_time = { NULL, NULL, 0, sizeof(double) };
    struct list_fifo type2_time = { NULL, NULL, 0, sizeof(double) };
    struct list *used_ptr = NULL;
    double t1, t2, t0, all_time = 0, type1_time_sum = 0, type2_time_sum = 0, temp_time = 0, avg_time;
    int count = 0, que_num = 0, flag = 100, sum1 = 0, sum2 = 0, kol = 0, input;
    int type1_in = 0, type1_out = 0, type2_in = 0, type2_out = 0, ejected = 0;

    srand(time(NULL));
    t1 = ((float)rand() / RAND_MAX) * (t1_max - t1_min) + t1_min;
    t2 = ((float)rand() / RAND_MAX) * (t2_max - t2_min) + t2_min;

    if (t1 <= t2)
    {
        list_fifo_add(&type1, NULL, &used_ptr);
        type1_in++;

        t0 = ((float)rand() / RAND_MAX) * (t3_max - t3_min) + t3_min;
        que_num = 1;
        t2 -= t1;
        all_time += t1;
        t1 = ((float)rand() / RAND_MAX) * (t1_max - t1_min) + t1_min;

        list_fifo_add(&type1_time, &all_time, NULL);
    }
    else
    {
        list_fifo_add(&type2, NULL, &used_ptr);
        type2_in++;

        t0 = ((float)rand() / RAND_MAX) * (t4_max - t4_min) + t4_min;
        que_num = 2;
        t1 -= t2;
        all_time += t2;
        t2 = ((float)rand() / RAND_MAX) * (t2_max - t2_min) + t2_min;

        list_fifo_add(&type2_time, &all_time, NULL);
    }

    while (count < MAX_COUNT)
    {
        if ((t1 <= t2) && ((!que_num) || (t1 <= t0)))
        {
            list_fifo_add(&type1, NULL, &used_ptr);
            type1_in++;

            all_time += t1;

            if (que_num == 1)
            {
                t0 -= t1;
            }
            else
            {
                if (que_num)
                {
                    list_fifo_delete(&type2, NULL, &used_ptr);
                    list_fifo_add(&type2, NULL, &used_ptr);
                    ejected++;

                    list_fifo_delete(&type2_time, &temp_time, NULL);
                    list_fifo_add(&type2_time, &temp_time, NULL);
                }
                t0 = ((float)rand() / RAND_MAX) * (t3_max - t3_min) + t3_min;
                que_num = 1;
            }

            t2 -= t1;
            t1 = ((float)rand() / RAND_MAX) * (t1_max - t1_min) + t1_min;

            list_fifo_add(&type1_time, &all_time, NULL);
        }
        else if ((t2 <= t1) && ((!que_num) || (t2 <= t0)))
        {
            list_fifo_add(&type2, NULL, &used_ptr);
            type2_in++;

            if (que_num)
            {
                t0 -= t2;
            }
            else
            {
                t0 = ((float)rand() / RAND_MAX) * (t4_max - t4_min) + t4_min;
                que_num = 2;
            }

            t1 -= t2;
            all_time += t2;
            t2 = ((float)rand() / RAND_MAX) * (t2_max - t2_min) + t2_min;

            list_fifo_add(&type2_time, &all_time, NULL);
        }
        else
        {
            t1 -= t0;
            t2 -= t0;
            all_time += t0;

            if (que_num == 1)
            {
                list_fifo_delete(&type1, NULL, &used_ptr);
                type1_out++;
                count++;

                list_fifo_delete(&type1_time, &temp_time, NULL);
                type1_time_sum += all_time - temp_time;
            }
            else
            {
                list_fifo_delete(&type2, NULL, &used_ptr);
                type2_out++;

                list_fifo_delete(&type2_time, &temp_time, NULL);
                type2_time_sum += all_time - temp_time;
            }

            if (type1.len)
            {
                t0 = ((float)rand() / RAND_MAX) * (t3_max - t3_min) + t3_min;
                que_num = 1;
            }
            else if (type2.len)
            {
                t0 = ((float)rand() / RAND_MAX) * (t4_max - t4_min) + t4_min;
                que_num = 2;
            }
            else
            {
                que_num = 0;
            }
        }

        sum1 += (int)type1.len;
        sum2 += (int)type2.len;
        kol++;

        if (count == flag)
        {
            flag += 100;
            printf("len1 = %d; len2 = %d; avg1 = %d; avg2 = %d\n", (int)type1.len, (int)type2.len, sum1 / kol, sum2 / kol);
        }
    }

    if ((t1_max + t1_min) / 2 >= (t3_max + t3_min) / 2)
        avg_time = (t1_max + t1_min) / 2 * MAX_COUNT;
    else
        avg_time = (t3_max + t3_min) / 2 * MAX_COUNT;

    printf("\nTotal time: %lf; Expected time: %lf; Difference: %.2lf%%\n"
           "Incoming requests of 1st type: %d; Released requests of 1st type: %d\n"
           "Incoming requests of 2nd type: %d; Released requests of 2nd type: %d\n"
           "Average time in queue for: Type 1 - %lf; Type 2 - %lf\n"
           "Ejected requests: %d\n", all_time, avg_time, fabs(all_time - avg_time) / avg_time * 100,
           type1_in, type1_out, type2_in, type2_out, type1_time_sum / type1_out,
           type2_time_sum / type2_out, ejected);

    printf("If you want to print list of free adresses enter 1\n");
    if ((scanf("%d", &input) == 1) && (input == 1))
    {
        printf("\nFree adresses: ");
        while (used_ptr)
        {
            printf("%p ", *(void**)used_ptr->value);
            used_ptr = used_ptr->next;
        }
        printf("\n");
    }

    list_fifo_free(&type1);
    list_fifo_free(&type2);
    list_fifo_free(&type1_time);
    list_fifo_free(&type2_time);
    list_free(used_ptr);
}

void vect_operation(double t1_min, double t1_max, double t2_min, double t2_max, double t3_min, double t3_max, double t4_min, double t4_max)
{
    struct vect_fifo type1 = { NULL, NULL, NULL, NULL, 0, sizeof(int) };
    struct vect_fifo type2 = { NULL, NULL, NULL, NULL, 0, sizeof(int) };
    struct vect_fifo type1_time = { NULL, NULL, NULL, NULL, 0, sizeof(double) };
    struct vect_fifo type2_time = { NULL, NULL, NULL, NULL, 0, sizeof(double) };
    vect_fifo_create(&type1, STACK_MAX, sizeof(int));
    vect_fifo_create(&type2, STACK_MAX, sizeof(int));
    vect_fifo_create(&type1_time, STACK_MAX, sizeof(double));
    vect_fifo_create(&type2_time, STACK_MAX, sizeof(double));

    double t1, t2, t0, all_time = 0, type1_time_sum = 0, type2_time_sum = 0, temp_time = 0, avg_time;
    int count = 0, que_num = 0, flag = 100, sum1 = 0, sum2 = 0, kol = 0;
    int type1_in = 0, type1_out = 0, type2_in = 0, type2_out = 0, ejected = 0;

    srand(time(NULL));
    t1 = ((float)rand() / RAND_MAX) * (t1_max - t1_min) + t1_min;
    t2 = ((float)rand() / RAND_MAX) * (t2_max - t2_min) + t2_min;

    if (t1 <= t2)
    {
        vect_fifo_add(&type1, NULL);
        type1_in++;

        t0 = ((float)rand() / RAND_MAX) * (t3_max - t3_min) + t3_min;
        que_num = 1;
        t2 -= t1;
        all_time += t1;
        t1 = ((float)rand() / RAND_MAX) * (t1_max - t1_min) + t1_min;

        vect_fifo_add(&type1_time, &all_time);
    }
    else
    {
        vect_fifo_add(&type2, NULL);
        type2_in++;

        t0 = ((float)rand() / RAND_MAX) * (t4_max - t4_min) + t4_min;
        que_num = 2;
        t1 -= t2;
        all_time += t2;
        t2 = ((float)rand() / RAND_MAX) * (t2_max - t2_min) + t2_min;

        vect_fifo_add(&type2_time, &all_time);
    }

    while (count < MAX_COUNT)
    {
        if ((t1 <= t2) && ((!que_num) || (t1 <= t0)))
        {
            vect_fifo_add(&type1, NULL);
            type1_in++;

            all_time += t1;

            if (que_num == 1)
            {
                t0 -= t1;
            }
            else
            {
                if (que_num)
                {
                    vect_fifo_get(&type2, NULL);
                    vect_fifo_add(&type2, NULL);
                    ejected++;

                    vect_fifo_get(&type2_time, &temp_time);
                    vect_fifo_add(&type2_time, &temp_time);
                }
                t0 = ((float)rand() / RAND_MAX) * (t3_max - t3_min) + t3_min;
                que_num = 1;
            }

            t2 -= t1;
            t1 = ((float)rand() / RAND_MAX) * (t1_max - t1_min) + t1_min;

            vect_fifo_add(&type1_time, &all_time);
        }
        else if ((t2 <= t1) && ((!que_num) || (t2 <= t0)))
        {
            vect_fifo_add(&type2, NULL);
            type2_in++;

            if (que_num)
            {
                t0 -= t2;
            }
            else
            {
                t0 = ((float)rand() / RAND_MAX) * (t4_max - t4_min) + t4_min;
                que_num = 2;
            }

            t1 -= t2;
            all_time += t2;
            t2 = ((float)rand() / RAND_MAX) * (t2_max - t2_min) + t2_min;

            vect_fifo_add(&type2_time, &all_time);
        }
        else
        {
            t1 -= t0;
            t2 -= t0;
            all_time += t0;

            if (que_num == 1)
            {
                vect_fifo_get(&type1, NULL);
                type1_out++;
                count++;

                vect_fifo_get(&type1_time, &temp_time);
                type1_time_sum += all_time - temp_time;
            }
            else
            {
                vect_fifo_get(&type2, NULL);
                type2_out++;

                vect_fifo_get(&type2_time, &temp_time);
                type2_time_sum += all_time - temp_time;
            }

            if (type1.len)
            {
                t0 = ((float)rand() / RAND_MAX) * (t3_max - t3_min) + t3_min;
                que_num = 1;
            }
            else if (type2.len)
            {
                t0 = ((float)rand() / RAND_MAX) * (t4_max - t4_min) + t4_min;
                que_num = 2;
            }
            else
            {
                que_num = 0;
            }
        }

        sum1 += (int)type1.len;
        sum2 += (int)type2.len;
        kol++;

        if (count == flag)
        {
            flag += 100;
            printf("len1 = %d; len2 = %d; avg1 = %d; avg2 = %d\n", (int)type1.len, (int)type2.len, sum1 / kol, sum2 / kol);
        }
    }

    if ((t1_max + t1_min) / 2 >= (t3_max + t3_min) / 2)
        avg_time = (t1_max + t1_min) / 2 * MAX_COUNT;
    else
        avg_time = (t3_max + t3_min) / 2 * MAX_COUNT;

    printf("\nTotal time: %lf; Expected time: %lf; Difference: %.2lf%%\n"
           "Incoming requests of 1st type: %d; Released requests of 1st type: %d\n"
           "Incoming requests of 2nd type: %d; Released requests of 2nd type: %d\n"
           "Average time in queue for: Type 1 - %lf; Type 2 - %lf\n"
           "Ejected requests: %d\n", all_time, avg_time, fabs(all_time - avg_time) / avg_time * 100,
           type1_in, type1_out, type2_in, type2_out, type1_time_sum / type1_out,
           type2_time_sum / type2_out, ejected);

    vect_fifo_free(&type1);
    vect_fifo_free(&type2);
    vect_fifo_free(&type1_time);
    vect_fifo_free(&type2_time);
}
