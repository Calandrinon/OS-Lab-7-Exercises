#include <stdio.h>
#include <time.h>
#include <signal.h>

void handler() {
	time_t t = time(NULL);
	char* mystr = ctime(&t);
	printf("%s\n", mystr);
}

int main() {
	/**
		The SIGHUP signal can be sent with the command "kill -1 process_id".
		SIGHUP has the number 1 associated with it, as it is written in the section 7 of the signal page in the manual.
	**/
	signal(SIGHUP, handler);
	while(1);
	return 0;
}
