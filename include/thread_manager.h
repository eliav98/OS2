//
// Created by Eliav on 05/06/2024.
//

#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include <vector>
#include <setjmp.h>
#include "thread.h"


class ThreadManager {
 public:
  ThreadManager();
  ~ThreadManager();

  int get_tid();
  int get_quantums(int tid);
  int get_total_quantums();

 private:
  int num_threads;
  int total_quantums;
  std::vector<Thread*> threads;
  int current_thread_index;
  sigjmp_buf main_env;

  void switch_to_thread(int index);
};

#endif // THREAD_MANAGER_H
