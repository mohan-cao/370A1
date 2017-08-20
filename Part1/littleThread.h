/*
 ============================================================================
 Name        : littleThread.h
 Author      : Robert Sheehan
 Version     : 1.0
 Description : header file for OS assignment 1 2017
 ============================================================================
 */

#include <setjmp.h>

/* The thread states */
enum state_t { SETUP, RUNNING, READY, FINISHED };

typedef struct thread {
	int tid;				// thread identifier
	void (*start)();		// the start function
	jmp_buf environment;	// saved registers
	enum state_t state;		// the state
	void *stackAddr;		// the stack address
	struct thread *prev;	// pointer to the previous thread
	struct thread *next;	// pointer to the next thread
} *Thread;
