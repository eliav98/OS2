#include <setjmp.h>
#include <iostream>

#define STACK_SIZE 4096

typedef void (*thread_entry_point)(void);

class Thread {
 public:
  enum State { READY, RUNNING, BLOCKED };

  Thread(int id, thread_entry_point entry_point);
  ~Thread();

  void saveContext();
  void loadContext();
  int getId() const;
  State getState() const;
  void setState(State state);

 private:
  int id;
  sigjmp_buf context;
  char stack[STACK_SIZE];
  State state;
  thread_entry_point entry_point;
};

Thread::Thread(int id, thread_entry_point entry_point)
    : id(id), entry_point(entry_point), state(READY) {}

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
