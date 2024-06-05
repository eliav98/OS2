#include "thread.h"

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
