//
// Created by noga on 02-Jun-24.
//

#include "../include/Thread.h"

class ThreadManager
{
  int num_threads;
  int total_quantums; //?
  sigjmp_buf thread_envs[2];

//  Thread threads[MAX_THREAD_NUM];
};

/** Returns the thread ID of the calling thread. */
int get_tid();

/** Returns the number of quantums the thread with ID tid was in RUNNING state */
int get_quantums(int tid);

/** Returns the total number of quantums since the library was initialized, including the current quantum. */
int get_total_quantums();