#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	int a, b, sum;
	printf("a="); scanf("%d", &a);	
	printf("b="); scanf("%d", &b);	
	
	int p[2]; //the pipe
	pipe(p);
	int pid = fork();

	if (pid == 0) {
		sum = a + b;
		close(p[0]);		
		write(p[1], &sum, sizeof(int));
		close(p[1]);
		exit(0);	
	} else {
		close(p[1]);
		read(p[0], &sum, sizeof(int));
		close(p[0]);
		printf("%d\n", sum);
		wait(0);
	}	

	return 0;
}
