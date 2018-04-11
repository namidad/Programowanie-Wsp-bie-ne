#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int pierwsza (int n);

void main(int argc, char* argv[]){
int licznikPierwszych=0,czyPierwsza;

for(int i=atoi(argv[1]); i<atoi(argv[2]);i++){
	czyPierwsza=pierwsza(i);
	if(czyPierwsza){
		++licznikPierwszych;
	}
}

exit(licznikPierwszych);
}


int pierwsza (int n){
int i; 

for(i=2;i*i<=n;i++){
	if(n%i == 0) return(0);
}

return (1);
}
