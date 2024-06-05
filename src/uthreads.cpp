// Created by noga on 02-Jun-24.

#include <iostream>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

#define MAIN_THREAD_ID 0

typedef unsigned long address_t;

#ifdef __x86_64__
#define JB_SP 6
#define JB_PC 7

address_t translate_address(address_t addr) {
  address_t ret;
  asm volatile("xor    %%fs:0x30,%0\n"
               "rol    $0x11,%0\n"
      : "=g" (ret)
      : "0" (addr));
  return ret;
}
#else
#define JB_SP 4
#define JB_PC 5

address_t translate_address(address_t addr) {
    address_t ret;
    asm volatile("xor    %%gs:0x18,%0\n"
                 "rol    $0x9,%0\n"
                 : "=g" (ret)
                 : "0" (addr));
    return ret;
}
#endif

#include "Thread.cpp"
#include "ThreadManager.cpp"

ThreadManager* threadManager = nullptr;

// void setup_thread(int tid, char* stack, thread_entry_point entry_point) {
//     address_t sp = (address_t)stack + STACK_SIZE - sizeof(address_t);
//     address_t pc = (address_t)entry_point;
//     sigsetjmp(env[tid], 1);
//     (env[tid]->__jmpbuf)[JB_SP] = translate_address(sp);
//     (env[tid]->__jmpbuf)[JB_PC] = translate_address(pc);
//     sigemptyset(&env[tid]->__saved_mask);
// }

int uthread_init(int quantum_usecs) {
  if (quantum_usecs <= 0) {
      std::cerr << "thread library error: Invalid quantum_usecs\n";
      return -1;
    }

  threadManager = new ThreadManager();
  if (!threadManager) {
      std::cerr << "system error: Memory allocation failed\n";
      return -1;
    }

  // Setup the main thread (tid = 0)
  // setup_thread(MAIN_THREAD_ID, nullptr, nullptr);

  // More initialization code as needed...

  return 0;
}

// Implement other functions...
