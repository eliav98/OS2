// Created by noga on 02-Jun-24.

#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
#include <iostream>

// Thread class declaration for completeness, you may want to move it if needed
class Thread {
 public:
  enum State { READY, RUNNING, BLOCKED };

  Thread(int id);
  ~Thread();

  void saveContext();
  void loadContext();
  int getId() const;
  State getState() const;
  void setState(State state);

 private:
  int id;
  jmp_buf context;
  char stack[4096];
  State state;
};

Thread::Thread(int id) : id(id), state(READY) {}

Thread::~Thread() {}

void Thread::saveContext() {
  sigsetjmp(context, 1);
}

void Thread::loadContext() {
  siglongjmp(context, 1);
}

int Thread::getId() const {
  return id;
}

Thread::State Thread::getState() const {
  return state;
}

void Thread::setState(State state) {
  this->state = state;
}

// ThreadManager class definition
class ThreadManager
{
 public:
  ThreadManager();
  ~ThreadManager();

  int get_tid();
  int get_quantums(int tid);
  int get_total_quantums();

 private:
  int num_threads;
  int total_quantums; //?
  sigjmp_buf thread_envs[2];

  // Thread threads[MAX_THREAD_NUM];
};

ThreadManager::ThreadManager() : num_threads(0), total_quantums(0) {}

ThreadManager::~ThreadManager() {}

int ThreadManager::get_tid() {
  // Implement logic to get the thread ID of the calling thread
  return 0; // Placeholder return value
}

int ThreadManager::get_quantums(int tid) {
  // Implement logic to return the number of quantums the thread with ID tid was in RUNNING state
  return 0; // Placeholder return value
}

int ThreadManager::get_total_quantums() {
  // Implement logic to return the total number of quantums since the library was initialized
  return total_quantums;
}

// Main function to demonstrate usage (if needed)
int main() {
  ThreadManager manager;
  std::cout << "Total quantums: " << manager.get_total_quantums() << std::endl;
  return 0;
}
