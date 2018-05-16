#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <string.h>
#include <mqueue.h>


struct {
	int pocz;
	int kon;
	int wynik;
} wyn;

int pierwsza (int n);

void main(int argc, char** args){
	int licznikPierwszych=0;
	int poczatek = atoi(args[1]);
	int koniec = atoi(args[2]);

	int fifo,zapis;

	for(int i=poczatek; i<koniec;i++){
		if(pierwsza(i)==1){
			licznikPierwszych++;
		}

	}
	fifo = open("FIFO", O_RDWR);

	wyn.pocz=poczatek;
	wyn.kon=koniec;
	wyn.wynik=licznikPierwszych;

	zapis = write(fifo,&wyn,sizeof(wyn));

	close(fifo);
}


int pierwsza (int n){
int i; 

for(i=2;i*i<=n;i++){
	if(n%i == 0) { return(0);}
}
	return (1);
}
