/*
	The threads.
*/

void thread2();

void thread1() {
	int i;
	for (i = 0; i < 5; i++)
		puts("hi");
    thread2();
}

void thread2() { 
	int i;
	for (i = 0; i < 5; i++)
		puts("bye");
}

const int NUMTHREADS = 2;

typedef void (*threadPtr)();

threadPtr threadFuncs[] = {thread1, thread2};
