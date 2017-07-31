/*
 ============================================================================
 Name        : OSA1.c
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
ThreadManager tm = NULL;
struct sigaction setUpAction;

ThreadManager loadThreadMgr(Thread*);
Thread finishThread(ThreadManager);

/*
 * Switches execution from prevThread to nextThread.
 */
void switcher(Thread* threadArray) {
	if(!tm) tm = loadThreadMgr(threadArray);
	// put threadArray into ThreadManager
	if (tm->head->state == FINISHED) { // it has finished
		printf("\ndisposing %d\n", tm->head->tid);
		free(tm->head->stackAddr); // Wow!
		finishThread(tm);
		printThreadStates(threadArray);
		longjmp(tm->head->environment, 1); //finishThread moves the head along by one, so essentially the same as head -> next
	} else if (setjmp(tm->head->environment) == 0) { // so we can come back here
		tm->head->state = READY;
		tm->head->next->state = RUNNING;
		printf("scheduling %d\n", tm->head->next->tid);
		longjmp(tm->head->next->environment, 1);
	}
}

/*
 * Loads the ThreadManager with a thread array
 */
ThreadManager loadThreadMgr(Thread* threadArray) {
	int size = sizeof(threadArray)/sizeof(Thread);
	ThreadManager tm = (ThreadManager)malloc(sizeof(ThreadManager));
	for(int i=0;i<size;i++){
		if(i == 0){
			tm->head = threadArray[0];
			tm->tail = threadArray[0];
			threadArray[0]->prev = threadArray[0];
			threadArray[0]->next = threadArray[0];
			continue;
		}
		tm->tail->next = threadArray[i];
		tm->head->prev = threadArray[i];
		threadArray[i]->next = tm->head;
		threadArray[i]->prev = tm->tail;
		tm->tail = threadArray[i];
	}
	return tm;
}

/*
 * Remove the head of the queue of the ThreadManager
 */
Thread finishThread(ThreadManager tm) {
	Thread t = tm->head;
	tm->tail = tm->head->next;
	tm->head->next->prev = tm->tail;
	tm->head = tm->head->next;
	return t;
}

/*
 * Prints thread states
 */
void printThreadStates(Thread* threads){
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
		localThread->next = mainThread;
		mainThread->prev = localThread;
		switcher(NULL); // at the moment back to the main thread
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
	return thread;
}

int main(void) {
	struct thread controller;
	Thread threads[NUMTHREADS];
	mainThread = &controller;
	mainThread->state = RUNNING;
	setUpStackTransfer();
	// create the threads
	for (int t = 0; t < NUMTHREADS; t++) {
		threads[t] = createThread(threadFuncs[t]);
	}
	printThreadStates(threads);
	puts("switching to first thread");
	switcher(threads);
	puts("back to the main thread");
	printThreadStates(threads);
	return EXIT_SUCCESS;
}
