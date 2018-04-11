#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char * argv[]){ 
int pid,i,j,status;
char number[20];
for(i=0; i<argc-2; i++){
	if ((pid = fork()) == 0) {
		execl("./pot","pot",number,argv[i+1], NULL);
	}
}

for(i=1;i< atoi(argv[1]); i++){
	printf("Macierzysty - krok %d \n",i);
	sleep(1);

}

for(i=0;i < argc-1;i++){
	pid = wait(&status);
	printf("Proces %d zakonczony, status %d\n",pid, status);
}

}
