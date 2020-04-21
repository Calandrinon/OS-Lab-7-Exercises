#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	
	if (argc != 3) {
		printf("The program takes two parameters: a word and a filename\n");	
		return 0;
	}
	
	int mypipe[2];
	pipe(mypipe);
	int child = fork();

	if (child == 0) {
		close(mypipe[0]);
		argv[0] = "grep";
		dup2(mypipe[1], 1); //1 is the file descriptor of stdout
		execvp("grep", argv);
		exit(0);
	}
	
	wait(0);
	close(mypipe[1]);
	
	char buffer[100], line[50], *current_char = buffer - 1;
	do {
		current_char++;
		read(mypipe[0], current_char, 1);
	} while(*current_char != '\0');
	close(mypipe[0]);
	current_char = line - 1;

	for(int i = 0; i <= strlen(buffer); i++) {
		do {
			current_char++;
			*current_char = buffer[i];
			i++;
		} while(*current_char != '\n' && *current_char != '\0');
		*current_char = '\0';	
		i--;
		if(strlen(line) % 3 == 0)
			printf("%s\n", line);

		current_char = line - 1;
	}

	wait(0);
	return 0;
}
