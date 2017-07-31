/*
	The threads.
*/

sigset_t signalSet;

void signalsOff() {
	if (sigemptyset(&signalSet) < 0) {
		perror("empty signal set");
		exit(EXIT_FAILURE);		
	}
	if (sigaddset(&signalSet, SIGVTALRM) < 0) {
		perror("add sigvtalrm");
		exit(EXIT_FAILURE);		
	}
	if (sigprocmask(SIG_BLOCK, &signalSet, NULL) < 0) { // block SIGVTALRM
		perror("block signal");
		exit(EXIT_FAILURE);
	}	
}

void signalsOn() {
	if (sigprocmask(SIG_UNBLOCK, &signalSet, NULL) < 0) {
		perror("unblock signal");
		exit(EXIT_FAILURE);
	}	
}

int wasteTime(int number) {
	int i, j;
	int result = 0;

	for (i = 0; i < 10000; i++)
		for (j = 0; j < number; j++) {
			signalsOff();
			result = rand();
			signalsOn();
		}
	return result;
}

void thread1() {
	int i;
	for (i = 0; i < 5; i++) {
		wasteTime(10);
		// signalsOff();
		puts("hi");
		printf("%d\n", wasteTime(10));
		// signalsOn();
	}
}

void thread2() { 
	int i;
	for (i = 0; i < 5; i++) {
		wasteTime(20);
		// signalsOff();
		puts("bye");
		printf("%d\n", wasteTime(20));
		// signalsOn();
	}
}

const int NUMTHREADS = 3;

typedef void (*threadPtr)();

threadPtr threadFuncs[] = {thread1, thread2, thread2};
