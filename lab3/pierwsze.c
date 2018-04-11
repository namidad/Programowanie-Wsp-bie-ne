#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h> 
#include <sys/stat.h> 

struct {
	int pocz;
	int kon;
	int wynik;
} wyn_t;

void main(int argc, char** args){ 
	//oczyt i zapis | jezeli plik nie isnieje => stworz go |  obetnij plik do 0
	int poczatek_zakresu=atoi(args[1]);
	int koniec_zakresu=atoi(args[2]);
	int liczba_procesow=atoi(args[3]);
	char pocz_zak[20];
	char kon_zak[20];
	int pid,rd;
	int status;
	int suma;
	int przedzial = ((koniec_zakresu-poczatek_zakresu)/liczba_procesow);
	int plik = open ("plik.txt", O_RDWR | O_CREAT | O_TRUNC,0666); 
	if (plik<0){
		perror("Open error!");
	}
	

	for(int i=0; i<liczba_procesow;i++){
	//aby moc uzyc funkcji excl, tworzymy string
	//poczatek przedzialu
	sprintf(pocz_zak, "%d", poczatek_zakresu+(i*przedzial));
	//koniec przedzialu
	sprintf(kon_zak, "%d", poczatek_zakresu+(i*przedzial)+przedzial);

	if((pid=fork())==0){
	execl("./licz","licz",pocz_zak,kon_zak,NULL);
	}

	}

	for(int i=0;i<liczba_procesow;i++){
	pid = wait(&status);	
	}
	
	for(int i=0;i<liczba_procesow;i++){
	   rd = read(plik,&wyn_t,sizeof(wyn_t));
	   suma=suma+wyn_t.wynik;
	   printf("rd: %d Pocz prz: %d Koniec prz: %d Liczb P: %d\n",rd,wyn_t.pocz,wyn_t.kon,wyn_t.wynik);
	}
	printf("Lacznie wyszlo: %d liczb pierwszych \n",suma);
	close(plik);
}
