/*
	The original thread.
*/

void thread1() {
	int i;
	for (i = 0; i < 10; i++)
		puts("hi");
}

const int NUMTHREADS = 1;

typedef void (*threadPtr)();

threadPtr threadFuncs[] = {thread1};
