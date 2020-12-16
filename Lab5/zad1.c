#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAXBUF 10

int main(int argc, char* argv[]) {

	int pdesk[2];
	pipe(pdesk);

	if(fork() == 0){							// 
		char string[MAXBUF];
		while (read(pdesk[0], string, MAXBUF)){
			if(string[MAXBUF - 1] == 0)
				break;
			printf("#%s#\n", string);
		}
	}

	else{
		FILE *fp;
		char string[MAXBUF];
		char* filename = "argv[1]";

		fp = fopen(argv[1], "r");

		while(fgets(string, MAXBUF, fp) != NULL){
			string[MAXBUF - 1] = 1;
			write(pdesk[1], string, MAXBUF);
		}

		fclose(fp);
	}
	return 0;
}