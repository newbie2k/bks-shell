/**
 * @author      : Bhaskar Singh (bhaskar.kernel@gmail.com)
 * @file        : bks.c
 * @created     : Sunday Jun 23, 2019 00:44:40 IST
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SPACE 0
#define NEWLINE 1

short STATUS = SPACE;

/**
 * getString Function will take variable character inputs
 * until it reach to Space Character or NewLine Character.
 */

char* getString(void) {

    char *word;
    int c,n=1;
	STATUS = SPACE;


    word = malloc(sizeof(char) * 1);              // Assinged by malloc because word is going to used by realloc function.


    while((c = getchar()) != ' ' ) {
		
		if(c == '\n') {
			STATUS = NEWLINE;                     // Used to Know how getString() function return by pressing ENTER KEY or SPACE KEY
			break;
		}
        word = realloc(word, n + 1);
        word[n - 1] = c;
        word[n] = '\0';
        n++;
    }
    return word;

}

/**
 * Commands is the first word and words are seprated by Space,
 * Options must have dash(-) as prefix and argument are those words
 * which came after Options i.e. words which have dash(-) as prefix.
 */

int main(void) {
	 char *cmd = NULL, *opt = NULL, *arg = NULL, *tmp = NULL;
    
	do{	
	    printf("\nbks >$ ");
	    cmd = getString();
		if(STATUS != NEWLINE) {                 // If ENTER KEY is not press i.e. we press SPACE KEY and about to give Options or Argument.
			tmp = getString();
			if(tmp[0] == '-') {                 // If have Options
				opt = tmp;
				arg = getString();              // Argument After Options
			}
			else 
				arg = tmp;                      // Argument without Option
		}
		printf("Command = %s, Argument = %s and Option = %s ",cmd,opt,arg);
		
	}while((strcmp(cmd,"quit") != 0) && (strcmp(cmd,"exit") != 0));        // Type "quit" or "exit" (without quots) to exit from program.

}


