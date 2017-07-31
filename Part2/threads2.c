/*
	The threads.
*/

void threadYield();

void thread1() {
	int i;
	for (i = 0; i < 2; i++) {
		puts("hi");
		threadYield();
	}
}

void thread2() { 
	int i;
	for (i = 0; i < 2; i++) {
		puts("bye");
		threadYield();
	}
}

const int NUMTHREADS = 3;

typedef void (*threadPtr)();

threadPtr threadFuncs[] = {thread1, thread2, thread2};
