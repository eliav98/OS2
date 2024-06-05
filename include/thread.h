//
// Created by Eliav on 05/06/2024.
//

#ifndef THREAD_H
#define THREAD_H

#include <setjmp.h>

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

#endif // THREAD_H
