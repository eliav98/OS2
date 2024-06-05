#include "thread_manager.h"

ThreadManager::ThreadManager() : num_threads(0), total_quantums(0), current_thread_index(-1) {}

ThreadManager::~ThreadManager() {
  for (auto& thread : threads) {
      delete thread;
    }
}

int ThreadManager::get_tid() {
  if (current_thread_index >= 0 && current_thread_index < threads.size()) {
      return threads[current_thread_index]->getId();
    }
  return -1;
}

int ThreadManager::get_quantums(int tid) {
  // Placeholder implementation
  return 0;
}

int ThreadManager::get_total_quantums() {
  return total_quantums;
}

void ThreadManager::switch_to_thread(int index) {
  if (current_thread_index != index) {
      int previousThreadIndex = current_thread_index;
      current_thread_index = index;
      if (previousThreadIndex >= 0 && previousThreadIndex < threads.size()) {
          threads[previousThreadIndex]->saveContext();
        }
      threads[current_thread_index]->loadContext();
    }
}
