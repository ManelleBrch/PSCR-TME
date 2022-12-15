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
#include <unordered_map>


int main(int argc, char* argv[]){

	std::unordered_map<std::string, std::string> map;
	int sock;
	int port = atoi(argv[2]);
	char msg[80];

	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1){
		perror("Erreur création socket");
		exit(1);
	}

	struct sockaddr_in exp; //pour info expediteur
	int lenexp = sizeof(exp);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if(bind(sock,(struct sockaddr*)&addr, sizeof(addr)) < 0){
		perror("erreur bind");
		exit(1);
	}

	if(recvfrom(sock, msg, sizeof(msg), 0, (struct sockaddr *)&exp,&lenexp) == -1){
		perror("recvfrom");
	}



}
