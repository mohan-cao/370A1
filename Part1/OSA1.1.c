/*
 ============================================================================
 Name        : OSA1.1.c
 Author      : Mohan Cao (mcao024)
 Version     : 1.0
 Description : Single thread implementation.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "littleThread.h"
#include "threads0.c" // rename this for different threads

Thread newThread; // the thread currently being set up
Thread mainThread; // the main thread
Thread threads[NUMTHREADS]; // thread array
struct sigaction setUpAction;

void printThreadStates();
void scheduler(Thread origThread, Thread nextThread);

void scheduler(Thread origThread, Thread nextThread){ //TODO: make scheduler work
	if(nextThread==NULL){
		scheduler(origThread,origThread->next);
	}
}

/*
 * Switches execution from prevThread to nextThread.
 */
void switcher(Thread prevThread, Thread nextThread) {
	if (prevThread->state == FINISHED) { // it has finished
		printf("\ndisposing %d\n", prevThread->tid);
		free(prevThread->stackAddr); // Wow!
		printThreadStates(); // PRINTING AFTER FREEING. DOES IT WORK?
		longjmp(nextThread->environment, 1);
	} else if (setjmp(prevThread->environment) == 0) { // so we can come back here
		prevThread->state = READY;
		nextThread->state = RUNNING;
		printf("scheduling %d\n", nextThread->tid);
		printThreadStates();
		longjmp(nextThread->environment, 1);
	}
}

/*
 * Prints thread states
 */
void printThreadStates(){
    int size = sizeof(threads)/sizeof(Thread);
    printf("Thread States\n");
    printf("=============\n");
    char* state;
    for(int i=0;i<size;i++){
        switch(threads[i]->state){
            case SETUP:
                state = "setup";
                break;
            case RUNNING:
                state = "running";
                break;
            case READY:
                state = "ready";
                break;
            case FINISHED:
                state = "finished";
                break;
        }
        printf("threadID: %d state:%s\n", threads[i]->tid, state);
    }
}

/*
 * Associates the signal stack with the newThread.
 * Also sets up the newThread to start running after it is long jumped to.
 * This is called when SIGUSR1 is received.
 */
void associateStack(int signum) {
	Thread localThread = newThread; // what if we don't use this local variable?
	localThread->state = READY; // now it has its stack
	if (setjmp(localThread->environment) != 0) { // will be zero if called directly
		(localThread->start)();
		localThread->state = FINISHED;
		switcher(localThread, mainThread); // TODO: at the moment back to the main thread
	}
}

/*
 * Sets up the user signal handler so that when SIGUSR1 is received
 * it will use a separate stack. This stack is then associated with
 * the newThread when the signal handler associateStack is executed.
 */
void setUpStackTransfer() {
	setUpAction.sa_handler = (void *) associateStack;
	setUpAction.sa_flags = SA_ONSTACK;
	sigaction(SIGUSR1, &setUpAction, NULL);
}

/*
 *  Sets up the new thread.
 *  The startFunc is the function called when the thread starts running.
 *  It also allocates space for the thread's stack.
 *  This stack will be the stack used by the SIGUSR1 signal handler.
 */
Thread createThread(void (startFunc)()) {
	static int nextTID = 0;
	static Thread headOfList = NULL;
	Thread thread;
	stack_t threadStack;

	if ((thread = malloc(sizeof(struct thread))) == NULL) {
		perror("allocating thread");
		exit(EXIT_FAILURE);
	}
	thread->tid = nextTID++;
	thread->state = SETUP;
	thread->start = startFunc;
	if ((threadStack.ss_sp = malloc(SIGSTKSZ)) == NULL) { // space for the stack
		perror("allocating stack");
		exit(EXIT_FAILURE);
	}
	thread->stackAddr = threadStack.ss_sp;
	threadStack.ss_size = SIGSTKSZ; // the size of the stack
	threadStack.ss_flags = 0;
	if (sigaltstack(&threadStack, NULL) < 0) { // signal handled on threadStack
		perror("sigaltstack");
		exit(EXIT_FAILURE);
	}
	newThread = thread; // So that the signal handler can find this thread
	kill(getpid(), SIGUSR1); // Send the signal. After this everything is set.

	//set next and prev of the circular linked list
	if(headOfList == NULL) { // exactly 1 item in circular linked list
		headOfList = thread;
		headOfList->next,headOfList->prev = thread;
	}else if(headOfList->prev==headOfList){ // exactly 2 items in circular linked list
		headOfList->next = thread;headOfList->prev = thread;
		thread->next = headOfList;thread->prev = headOfList;
	}else{ // all others
		thread->next = headOfList;thread->prev = headOfList->prev;
		headOfList->prev->next = thread;
		headOfList->next->prev = thread;
	}

	return thread;
}

int main(void) {
	struct thread controller;
	mainThread = &controller;
	mainThread->state = RUNNING;
	setUpStackTransfer();
	// create the threads
	for (int t = 0; t < NUMTHREADS; t++) {
		threads[t] = createThread(threadFuncs[t]);
	}
    printThreadStates();
	puts("switching to first thread");
	switcher(mainThread, threads[0]);
	puts("back to the main thread");
    printThreadStates();
	return EXIT_SUCCESS;
}
