//
// Created by Eliav on 05/06/2024.
//


/*
 * sigsetjmp/siglongjmp demo program.
 * Hebrew University OS course.
 * Author: OS, os@cs.huji.ac.il
 */

#include "../include/ThreadManager.h"
#include "uthreads.h"
#include "Thread.h"
#include "ThreadManager.h"
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>


#define MAIN_THREAD_ID 0

#ifdef __x86_64__
/* code for 64 bit Intel arch */

typedef unsigned long address_t;
#define JB_SP 6
#define JB_PC 7

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
  address_t ret;
  asm volatile("xor    %%fs:0x30,%0\n"
               "rol    $0x11,%0\n"
      : "=g" (ret)
      : "0" (addr));
  return ret;
}

#else
/* code for 32 bit Intel arch */

typedef unsigned int address_t;
#define JB_SP 4
#define JB_PC 5


/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%gs:0x18,%0\n"
                 "rol    $0x9,%0\n"
    : "=g" (ret)
    : "0" (addr));
    return ret;
}


#endif

#define SECOND 1000000
#define STACK_SIZE 4096

typedef void (*thread_entry_point)(void);

char stack0[STACK_SIZE];
char stack1[STACK_SIZE];
sigjmp_buf env[2];
int current_thread = -1;


void jump_to_thread(int tid)
{
  current_thread = tid;
  siglongjmp(env[tid], 1);
}

/**
 * @brief Saves the current thread state, and jumps to the other thread.
 */
void yield(void)
{
  int ret_val = sigsetjmp(env[current_thread], 1);
  printf("yield: ret_val=%d\n", ret_val);
  bool did_just_save_bookmark = ret_val == 0;
//    bool did_jump_from_another_thread = ret_val != 0;
  if (did_just_save_bookmark)
    {
      jump_to_thread(1 - current_thread);
    }
}


void thread0(void)
{
  int i = 0;
  while (1)
    {
      ++i;
      printf("in thread0 (%d)\n", i);
      if (i % 3 == 0)
        {
          printf("thread0: yielding\n");
          yield();
        }
      usleep(SECOND);
    }
}


void thread1(void)
{
  int i = 0;
  while (1)
    {
      ++i;
      printf("in thread1 (%d)\n", i);
      if (i % 5 == 0)
        {
          printf("thread1: yielding\n");
          yield();
        }
      usleep(SECOND);
    }
}


void setup_thread(int tid, char *stack, thread_entry_point entry_point)
{
  // initializes env[tid] to use the right stack, and to run from the function 'entry_point', when we'll use
  // siglongjmp to jump into the thread.
  address_t sp = (address_t) stack + STACK_SIZE - sizeof(address_t);
  address_t pc = (address_t) entry_point;
  sigsetjmp(env[tid], 1);
  (env[tid]->__jmpbuf)[JB_SP] = translate_address(sp);
  (env[tid]->__jmpbuf)[JB_PC] = translate_address(pc);
  sigemptyset(&env[tid]->__saved_mask);
}


void setup(void)
{
  // sets up the threads, so they'll have the wanted initial SP and PC.
  setup_thread(0, stack0, thread0);
  setup_thread(1, stack1, thread1);
}


int main(void)
{
  setup();
  jump_to_thread(0);
  return 0;
}


/**
 * @brief initializes the thread library.
 *
 * Once this function returns, the main thread (tid == 0) will be set as RUNNING. There is no need to
 * provide an entry_point or to create a stack for the main thread - it will be using the "regular" stack and PC.
 * You may assume that this function is called before any other thread library function, and that it is called
 * exactly once.
 * The input to the function is the length of a quantum in micro-seconds.
 * It is an error to call this function with non-positive quantum_usecs.
 *
 * @return On success, return 0. On failure, return -1.
*/
int uthread_init(int quantum_usecs){
  ThreadManager *threadManager = new ThreadManager();
  setup_thread(MAIN_THREAD_ID, stack0, thread0);

}




/**
 * @brief Creates a new thread, whose entry point is the function entry_point with the signature
 * void entry_point(void).
 *
 * The thread is added to the end of the READY threads list.
 * The uthread_spawn function should fail if it would cause the number of concurrent threads to exceed the
 * limit (MAX_THREAD_NUM).
 * Each thread should be allocated with a stack of size STACK_SIZE bytes.
 * It is an error to call this function with a null entry_point.
 *
 * @return On success, return the ID of the created thread. On failure, return -1.
*/
int uthread_spawn(thread_entry_point entry_point){

}



