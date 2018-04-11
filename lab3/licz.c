#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <string.h>

struct {
	int pocz;
	int kon;
	int wynik;
} wyn_t;

int pierwsza (int n);

void main(int argc, char** args){
int licznikPierwszych=0;
char suma[16];
int poczatek = atoi(args[1]);
int koniec = atoi(args[2]);
int plik = open ("plik.txt", O_RDWR | O_APPEND); 
if (plik<0){
		perror("Open error!");
	}
	


for(int i=poczatek; i<koniec;i++){
	

	if(pierwsza(i)==1){
		licznikPierwszych++;
	}

}
wyn_t.pocz = poczatek;
wyn_t.kon = koniec;
wyn_t.wynik = licznikPierwszych;

printf("Czekam... \n");
lockf(plik,F_LOCK,0);
printf("Zalozenie blokady \n");
write(plik, &wyn_t, sizeof(wyn_t));
lockf(plik,F_ULOCK,0);
printf("Zdjecie blokady \n");
close(plik);
printf("wychodze \n");
}


int pierwsza (int n){
int i; 

for(i=2;i*i<=n;i++){
	if(n%i == 0) { return(0);}
}
	return (1);
}
