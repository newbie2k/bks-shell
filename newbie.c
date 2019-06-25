/**
 * @author      : Bhaskar Singh (bhaskar.kernel@gmail.com)
 * @file        : newbie.c
 * @created     : Sunday Jun 23, 2019 00:44:40 IST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 16
#define NEWLINE 1
#define RESET 0

short PRESSED_KEY = RESET;

/**
 * readinput()
 *
 * This will take variable character inputs
 * until it reach to Space Character or NewLine Character.
 */

char *readinput(void) {
	char *word;
	int c;      // store character temporarly
	int n = 1;  // Used to increase the size of word
	int count = 0;

	word =
	    malloc(sizeof(char) * SIZE);  // Assinged by malloc because word is
					  // going to used by realloc function.
	word[0] = '\0';   // Handle Error!

	while ((c = getchar()) != ' ') {
		if (c == '\n') {
			/* Used to Know how readinput() function return by
			   pressing ENTER KEY or SPACE KEY */
			PRESSED_KEY = NEWLINE;
			return word;
		}

		if (count == SIZE * n)  // Increasing Size
			word = realloc(word, SIZE * n);

		word[count++] = c;
		word[count] = '\0';
	}
	if(word[0] == '\0') {    // Handle Error! if command start with SPACES
		while(getchar() != '\n');
		PRESSED_KEY = NEWLINE;
	}
	return word;
}

int runcommand(char *cmd, char **argv) {
	pid_t pid;
	int status;

	pid = fork();

	if (pid < 0) {
		printf("Error!!!");
	}
	if (pid == 0) {
		execvp(cmd, argv);
	}
	if (pid > 0) {
		pid = wait(&status);
	}
}
/**
 * Commands is the first word and words are seprated by Space,
 * Options must have dash(-) as prefix and argvument are those words
 * which came after Options i.e. words which have dash(-) as prefix.
 *
 * COMMAND -OPTIONS(optional) ARGUMENT#1(optional) ARGUMENT#2(optional)
 */

int main(void) {
	char **argv;
	char *usrname = NULL;  // USER Env Variable Value

	usrname = getenv("USER");
	
	while (1) {
		int n = 1;  // Used to increase the size of word
		int count = 0;
		PRESSED_KEY = RESET;

		argv = malloc(sizeof(char *) * SIZE);

		printf("newbie@%s >$ ", usrname);  // Shell Prompt

		while (PRESSED_KEY != NEWLINE) {
			if (count == (SIZE * n) - 2) {
				n++;
				/* Increasing Size */
				argv = realloc(argv, SIZE * n);
			}
			argv[count] = readinput();
			argv[count + 1] = NULL;
			count++;
		}
		if ((strcmp(argv[0], "quit") == 0) ||
		    (strcmp(argv[0], "exit") ==
		     0)) {  // Type "quit" or "exit" (without quots) to exit
			    // from program.
			printf("\nThank You for Using newbie shell\n");
			free(argv);
			break;
		} else {
			fflush(stdout);
			if(*argv[0] == '\0') {
				free(argv);
				continue;
			}
			runcommand(argv[0], argv);
		}
		free(argv);
	}
}
