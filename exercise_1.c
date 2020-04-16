#include <stdio.h>
#include <signal.h>

void signal_handler() {
	printf("You can't close the program!\n");
}

int main() {
	/**
		The program can still be stopped if we send a SIGKILL signal.
		This can be done from the terminal by using the command "kill -9 process_id"	
	**/	

	signal(SIGINT, signal_handler);		
	signal(SIGTERM, signal_handler);

	while (1) {}

	return 0;
}
