#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	int a, b;
	printf("a="); scanf("%d", &a);	
	printf("b="); scanf("%d", &b);	

	int pid = fork();

	if (pid == 0) {
		printf("%d\n", a+b);
	} else {

		wait(0);
	}	

	return 0;
}
