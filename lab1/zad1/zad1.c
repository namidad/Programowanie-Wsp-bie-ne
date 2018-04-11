#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char * argv[]){
int pid,status,i,j;
for(i=0;i<argc-2;i++){

	if((pid = fork()) == 0) {
		printf("Proces potomny PID: %d \n", getpid());
		for(j=0;j<atoi(argv[i+2]);j++){
			printf("potomny: %d krok: %d \n", i,j+1);
			sleep(1);
		}
	exit(i);
	}
}

for(i=0; i< atoi(argv[1]); i++){
	printf("Macierzysty = %d \n", getpid());
	sleep(1);
}

for(i=0 ;i<argc-2;i++)
{
	pid = wait(&status);
	printf("Proces %d zakonczony, status %d \n", pid, WEXITSTATUS(status));
}
return 0;
}
