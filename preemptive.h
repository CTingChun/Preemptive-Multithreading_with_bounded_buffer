/*
 * file: preemptive.h
 *
 * this is the include file for the preemptive multithreading
 * package.  It is to be compiled by SDCC and targets the EdSim51 as
 * the target architecture.
 *
 * CS 3423 Fall 2018
 */

#ifndef __PREEMPTIVE_H__
#define __PREEMPTIVE_H__

#define MAXTHREADS 4  /* not including the scheduler */
/* the scheduler does not take up a thread of its own */
__idata __at (0x20) char savedSP[MAXTHREADS];
__idata __at (0x24) char threadBitmap[MAXTHREADS];
__idata __at (0x28) char ID;
__idata __at (0x29) char tmp;
__idata __at (0x2A) char i;
__idata __at (0x2B) char currentID;
__idata __at (0x2C) char managerID;
#define CNAME(s) _ ## s
#define LABELNAME(label) label ## $

typedef char ThreadID;
typedef void (*FunctionPtr)(void);

ThreadID ThreadCreate(FunctionPtr);
void ThreadYield(void);
void ThreadExit(void);
#define SemaphoreWaitBody(S, label) \
{ __asm \
LABNAME(label): \
    mov ACC, CNAME(S)\
    JB ACC.7, LABELNAME(label)\
    dec  CNAME(S) \
__endasm; }
#define SemaphoreCreate(s, n) s = n;
// create a counting semaphore s that is initialized to n
#define SemaphoreWait(s) SemaphoreWaitBody(s, __COUNTER__);
// do (busy-)wait() on semaphore s
#define SemaphoreSignal(s) {__asm INC CNAME(s) __endasm;}
// signal() semaphore s
#endif // __PREEMPTIVE_H__
