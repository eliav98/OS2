//
// Created by noga on 02-Jun-24.
//


#ifndef _THREAD_H_
#define _THREAD_H_

class ThreadDescriptor {
 public:
  enum Mode {
      RUNNING, READY, BLOCKED
  };

  int tid;
  Mode mode;
  int num_quantums;
};

#endif //_THREAD_H_
