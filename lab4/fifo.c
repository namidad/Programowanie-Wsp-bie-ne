#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <mqueue.h>


struct {
	int pocz; // poczatek przedzialu
	int kon; // koniec pprzedzialu
	int ile; // ile licz w przedziale
} wynik;

int main(int argc, char* argv[]){ 
// przyjmujemy 4 argumenty
// 1 argument - poczatek przedzialu
// 2 arugment - koniec przedzialu
// 3 argument - liczba podprocesow

	int poczatekPrzedzialu = atoi(argv[1]);
	int koniecPrzedzialu = atoi(argv[2]);
	int liczbaProcesow = atoi(argv[3]);
	char pocz_zak[20];
	char kon_zak[20];
	int przedzial=((koniecPrzedzialu-poczatekPrzedzialu)/liczbaProcesow);
	int pid, status,suma,odczyt,i;

	int fifo = mkfifo("FIFO", 0666);
	fifo = open("FIFO", O_RDWR);

	for(i=0;i<liczbaProcesow;i++){
		// do uzycia execl potrzebny string 
		// poczatek przedzialu i*przedzial
		sprintf(pocz_zak, "%d", poczatekPrzedzialu+(i*przedzial));
		//koniec przedzialu pocz_zak+przedzial
		sprintf(kon_zak, "%d", poczatekPrzedzialu+(i*przedzial)+przedzial);

		if((pid=fork())==0){
	
		execl("./licz","licz",pocz_zak,kon_zak,NULL);
		
		}


	}

	for(i=0; i<liczbaProcesow; i++)
	{
		pid = wait(&status);
		//printf("Proces %d zakończony status: %d\n", pid, status);
	}

	suma = 0;
	
	
	for(i=0;i<liczbaProcesow;i++){

	odczyt = read(fifo, &wynik, sizeof(wynik));
	printf("Poczatek: %d Koniec: %d Ilosc: %d\n",wynik.pocz,wynik.kon,wynik.ile);
	suma=suma+wynik.ile;
	}
	close(fifo);

	printf("Znaleziono %d liczb pierwszych\n", suma);
	return 0;

}

