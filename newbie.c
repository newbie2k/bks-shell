/**
 * @author      : Bhaskar Singh (bhaskar.kernel@gmail.com)
 * @file        : bks.c
 * @created     : Sunday Jun 23, 2019 00:44:40 IST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 16
#define SPACE 0
#define NEWLINE 1

short PRESSED_KEY = SPACE;

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

	PRESSED_KEY = SPACE;

	word =
	    malloc(sizeof(char) * SIZE);  // Assinged by malloc because word is
					  // going to used by realloc function.

	while ((c = getchar()) != ' ') {
		if (c == '\n') {
			/* Used to Know how readinput() function return by
			   pressing ENTER KEY or SPACE KEY */
			PRESSED_KEY = NEWLINE;
			break;
		}

		if (count == SIZE * n)  // Increasing Size
			word = realloc(word, SIZE * n);

		word[count++] = c;
		word[count] = '\0';
	}
	return word;
}


int runcommand(char *cmd, char **opt, char **arg) {
	pid_t pid;
	int status;

	pid = fork();

	if(pid < 0) {
		printf("Error while executing command!!!");
	}
	if(pid == 0) {
		printf("Inside Parent\n ");
		pid = wait(&status);
		printf("Process with ID = %d ... Exited Succesfully\n",getpid());
	}
	if(pid > 0 ) {
		printf("Inside Child Process PID = %d\n",pid);
		execvp(cmd,arg);
	}

	return 0;
}
/**
 * Commands is the first word and words are seprated by Space,
 * Options must have dash(-) as prefix and argument are those words
 * which came after Options i.e. words which have dash(-) as prefix.
 *
 * COMMAND -OPTIONS(optional) ARGUMENT#1(optional) ARGUMENT#2(optional)
 */

int main(void) {
	char **opt;
	char **arg;
	char *tmp = NULL;
	char *cmd = NULL;
	char *usrname = NULL;  // USER Env Variable Value
	char *path = NULL;     // PATH Env Variable Value

	opt = malloc(sizeof(char *) * SIZE);
	arg = malloc(sizeof(char *) * SIZE);
	usrname = getenv("USER");
	path = getenv("PATH");


	while (1) {
		int n = 1;  // Used to increase the size of word
		int opt_count = 0;
		int arg_count = 0;

		printf("newbie@%s >$ ",usrname);  // Shell Prompt
		cmd = readinput();

		if ((strcmp(cmd, "quit") == 0) || (strcmp(cmd, "exit") == 0)) {  // Type "quit" or "exit" (without quots) to exit from program.
			printf("\nThank You for Using newbie shell\n");
			break;
		}

		while (PRESSED_KEY == SPACE) {  // SPACE KEY pressed and about to give Options or Argument.
			tmp = readinput();

			if (tmp[0] == '-') {  // For Option

				/* count start from 0 and we need one extra
				   memory to store NULL thats way -2 insted of
				   -1 */
				if (opt_count == (SIZE * n) - 2) {
					n++;
					/* Increasing Size */
					opt = realloc(opt, SIZE * n);
				}
				opt[opt_count] = tmp;
				opt[opt_count + 1] = NULL;
				opt_count++;
			} else {  // For Argument
				if (arg_count == (SIZE * n) - 2) {
					n++;
					/* Increasing Size */
					arg = realloc(arg, SIZE * n);
				}
				arg[arg_count] = tmp;
				arg[arg_count + 1] = NULL;
				arg_count++;
			}
		runcommand(cmd, opt, arg);
		}
		/*printf("Command = %s\n", cmd);
		for (int i = 0; *(arg + i) != NULL; i++)
			printf("Arguments = %s\n", arg[i]);

		for (int i = 0; *(opt + i) != NULL; i++)
			printf("Options = %s\n", opt[i]); */
	}
		free(cmd);
		free(arg);
		free(opt);
}

