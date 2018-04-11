#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

void main(int argc, char* argv[]){ 
int pid, status,i, poczatekPrzedzialu, koniecPrzedzialu, liczbaProcesow;
poczatekPrzedzialu = atoi(argv[1]);
koniecPrzedzialu = atoi(argv[2]);
liczbaProcesow = atoi(argv[3]);
int N=(int)((koniecPrzedzialu-poczatekPrzedzialu)/liczbaProcesow);
int reszta=((koniecPrzedzialu-poczatekPrzedzialu) % liczbaProcesow);
int znalezione=0;
char poczPrz[20];
char konPrz[20];
time_t t1,t2;
t1=time(NULL);

for(i=0;i<liczbaProcesow;i++){
	if((pid = fork()) == 0){
		//sprintf uzywamy do konwersji 	liczby typu integer na lancuch znakow 
		//aby moc uzyc funkcji execl, do ktorej nie mozemy przekazac int
		sprintf(poczPrz, "%d", poczatekPrzedzialu+(i*N));
		if(i+1 == liczbaProcesow){
			sprintf(konPrz, "%d", koniecPrzedzialu+1);	
				
		} else {
			sprintf(konPrz, "%d", poczatekPrzedzialu+(i*N)+N);	
		}	
		execl("./licz.c", "licz", poczPrz, konPrz, NULL);
	
	} //koniec if
} // koniec for

for(i=0; i<liczbaProcesow; i++){
pid = wait(&status);
printf("Proces %d zakonczony status: %d \n", pid, status/256);
znalezione += WEXITSTATUS(status);
}


t2=time(NULL);
t2=t2-t1;
printf("\nIlosc znalezionych liczb pierwszych: %d \n Czas wyszukiwania  s \n",znalezione);

}
