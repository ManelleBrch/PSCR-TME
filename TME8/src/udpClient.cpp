#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string>
#include <netdb.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char* argv[]){
	int sock;
	struct sockaddr_in dest;
	int port = atoi(argv[argc-1]);
	char msg[128];
	char reponse[128];
	unsigned int lenrep = sizeof(reponse);

	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		perror("Erreur création socket");
		exit(1);
	}

	dest.sin_addr = htonl(atoi(argv[argc-2]));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(port);

	//contruction du message mais comprends pas comment message formé

	if (sendto(sock,msg,strlen(msg)+1,0,(struct sockaddr *)&dest, sizeof(dest)) == -1) {
		perror("sendto");
		exit(1);
	}

	//reception de la reponse
	if(recvfrom(sock, reponse, sizeof(reponse), 0, 0,&lenrep) == -1){
		perror("recvfrom");
	}
	printf("Reponse = %s", reponse);
	close(sock);
	return 0;

}
