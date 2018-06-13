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

typedef struct {
	int typ;	// typ zlecenia 
	int ile;	// liczba bajtow
	int fh;		// uchwyt pliku 
	char buf[SIZE];	// bufor 
} mms_t;

int main() {

struct sockaddr_in adr_moj, adr_cli;
int s, i, slen=sizeof(adr_cli),snd, rec, blen=sizeof(mms_t);
s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
mms_t msg;

printf("Czekam na instrukcje..");


// Ustalenie adresu IP nadawcy
memset((char *) &adr_moj, 0, sizeof(adr_moj));
adr_moj.sin_family = AF_INET;
adr_moj.sin_port = htons(PORT);
adr_moj.sin_addr.s_addr = htonl(INADDR_ANY);

   if (bind(s,(struct sockaddr *) &adr_moj, sizeof(adr_moj))==-1)
       printf("Błąd");


do {
	rec=recvfrom(s, &msg, blen, 0,(struct sockaddr *) &adr_cli, &slen);
	switch(msg.typ){
		case OPENR:
			msg.fh=open(msg.buf, O_RDONLY);
			break;
		case READ:
			msg.ile=read(msg.fh,msg.buf,SIZE);
			break;
		case OPENW:
			msg.fh=open(msg.buf, O_WRONLY|O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
			break;
		case WRITE:
			msg.ile=write(msg.fh,msg.buf, msg.ile);
			break;
		default:
			break;
	}
	rec=sendto(s,&msg,blen,0,(struct sockaddr *) &adr_cli,slen);
}while(1);

close(s);

}
