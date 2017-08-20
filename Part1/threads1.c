/*
	The threads.
*/

void thread1() {
	int i;
	for (i = 0; i < 5; i++)
		puts("hi");
}

void thread2() { 
	int i;
	for (i = 0; i < 5; i++)
		puts("bye");
}

const int NUMTHREADS = 2;

typedef void (*threadPtr)();

threadPtr threadFuncs[] = {thread1, thread2};
