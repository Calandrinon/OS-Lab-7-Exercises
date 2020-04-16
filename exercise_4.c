#include <stdio.h>
#include <sys/types.h>	
#include <sys/wait.h>	
#include <unistd.h>

int main() {
	for (int i = 0; i < 2; i++) {
		fork();
	}
	
	printf("pid %d\n", getpid());
	wait(0);	
	return 0;
}
