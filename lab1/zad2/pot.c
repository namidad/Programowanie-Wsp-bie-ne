#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char * argv[]){
int j;
for(j=1;j<=atoi(argv[2]);j++){
printf("potomny: %s krok %d \n", argv[1],j);
sleep(1);
}
exit(j);
}
