//
// Created by noga on 02-Jun-24.
//

#include "../include/ThreadManager.h"

int get_quantums(int tid)
{
    return threads[tid].num_quantums;
}

int get_total_quantums()
{
    return total_quantums;
}