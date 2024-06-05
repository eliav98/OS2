#include <vector>
#include <setjmp.h>

class Thread;

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
  int currentThreadIndex;
  sigjmp_buf main_env;

  void switchToThread(int index);
};

ThreadManager::ThreadManager() : num_threads(0), total_quantums(0), currentThreadIndex(-1) {}

ThreadManager::~ThreadManager() {
  for (auto& thread : threads) {
      delete thread;
    }
}

int ThreadManager::get_tid() {
  if (currentThreadIndex >= 0 && currentThreadIndex < threads.size()) {
      return threads[currentThreadIndex]->getId();
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

void ThreadManager::switchToThread(int index) {
  if (currentThreadIndex != index) {
      int previousThreadIndex = currentThreadIndex;
      currentThreadIndex = index;
      if (previousThreadIndex >= 0 && previousThreadIndex < threads.size()) {
          threads[previousThreadIndex]->saveContext();
        }
      threads[currentThreadIndex]->loadContext();
    }
}
