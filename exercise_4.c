#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
	char string[40];
	int pipe1[2], pipe2[2], word_lengths=0;
	pipe(pipe1);
	int first_child = fork();	

	if (first_child == 0) {
		close(pipe1[1]);

		while (1) {
			read(pipe1[0], string, sizeof(string));	

			if (string[0] == '\n') {
				break;
			} else { 
				word_lengths += strlen(string) - 1;
			}
		}

		printf("The total length of the words containing the diphthong \"oa\" is: %d\n", word_lengths);
		
		close(pipe1[0]);	
		exit(0);
	}


	pipe(pipe2);
	int second_child = fork();	

	if (second_child == 0) {
		close(pipe2[1]);

		while (1) {
			read(pipe2[0], string, sizeof(string));	

			if (string[0] == '\n') {
				break;
			} else { 
				word_lengths += strlen(string) - 1;
			}
		}
	
		printf("The total length of the words which don't contain the diphthong \"oa\" is: %d\n", word_lengths);
		
		close(pipe2[0]);	
		exit(0);
	}

	

	close(pipe1[0]);
	close(pipe2[0]);
	while (1) {
		fgets(string, 40, stdin);
		
		if (strlen(string) == 1) {
			write(pipe1[1], string, strlen(string));
			write(pipe2[1], string, strlen(string));
			break;
		} else if (strstr(string, "oa") != NULL) {
			write(pipe1[1], string, strlen(string));
		} else {		
			write(pipe2[1], string, strlen(string));
		}		
	}

	close(pipe1[1]);	
	close(pipe2[1]);		
	wait(0);
	wait(0);
	return 0;
}
