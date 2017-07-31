/*
 ============================================================================
 Name        : littleThread.h
 Author      : Mohan Cao (mcao024)
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

/* 
 * Thread manager (queue). Uses a circular linked list.
 */
typedef struct ThreadManager {
	struct thread *head; // read and dequeue from this end
	struct thread *tail; // queue onto this end
} *ThreadManager;
