 #include <arpa/inet.h>
 #include <netinet/in.h>
 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 

#define OPENR  1 // Otwarcie pliku do odczytu 
#define OPENW  2 // Otwarcie pliku do zapisu 
#define READ   3 // Odczyt fragmentu pliku 
#define CLOSE  4 // Zamkniecie pliku 
#define WRITE  5 // Zapis fragmentu pliku 
#define STOP  10 // Zatrzymanie serwera 
#define PORT 9952
#define SIZE 512  
#define BUFLEN 80 

typedef struct {
	int typ;	// typ zlecenia 
	int ile;	// liczba bajtow
	int fh;		// uchwyt pliku 
	char buf[SIZE];	// bufor 
} mms_t;

int main(int argc, char * argv[]) {


struct sockaddr_in adr_moj, adr_serw, adr_x;
int s, i, slen=sizeof(adr_serw), rec, blen=sizeof(mms_t), menu;
char buf[BUFLEN];
char name[100];
s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
mms_t msg;




// Ustalenie adresu IP nadawcy
memset((char *) &adr_serw, 0, sizeof(adr_serw));
adr_serw.sin_family = AF_INET;
adr_serw.sin_port = htons(PORT);
if (inet_aton(argv[1], &adr_serw.sin_addr)==0) {
        fprintf(stderr, "inet_aton() failed\n");
        _exit(1);
   }

printf("\n1. Czytaj z pliku\n2. Zapis do pliku\nTwoj wybor: ");
scanf("%d", &menu);


switch(menu){
	case 1:
		printf("\nPodaj nazwe pliku do odczytu: ");
		scanf("%s", name);
		msg.typ = OPENR;
		//tworzymy stringa z nazwy pliku i zapisujemy do msg.buf
		sprintf(msg.buf, "%s", name);
		int send;
		send=sendto(s, &msg, blen, 0,(struct sockaddr *)&adr_serw,(socklen_t) slen);
      		rec = recvfrom(s, &msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);	
		do{
		msg.typ = READ;
		send=sendto(s, &msg, blen, 0,(struct sockaddr *)&adr_serw,(socklen_t) slen);
		rec=recvfrom(s, &msg, blen, 0,(struct sockaddr *) &adr_x,(socklen_t *) &slen);
		printf("%s\n", msg.buf);
		}while(msg.ile==SIZE);

		break;
	case 2:
		
		break;
	
	default:
	
		break;
	


}

close(s);

return 0;
}
