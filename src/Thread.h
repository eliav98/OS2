//
// Created by noga on 02-Jun-24.
//

enum Mode {RUNNING, READY, BLOCKED};

#ifndef _THREAD_H_
#define _THREAD_H_

class Thread
{
    int tid;
    Mode mode;
    int num_quantums;
};


#endif //_THREAD_H_
