#ifndef SRC_SERVERSOCKET_H_
#define SRC_SERVERSOCKET_H_

#include "Socket.h"
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string>
#include <iosfwd>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>

namespace pr {

class ServerSocket {
	int socketfd;

public :
	// Demarre l'ecoute sur le port donne
	ServerSocket(int port) {
		socketfd = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = INADDR_ANY;
		if(bind(socketfd,(struct sockaddr*)&addr, sizeof(addr)) < 0){
			perror("erreur bind");
			exit(1);
		}
		listen(socketfd, 10);

	}
	int getFD() { return socketfd;}
	bool isOpen() const {return socketfd != -1;}

	Socket accept(){
		int fd;
		struct sockaddr_in exp;
		socklen_t sz = sizeof(exp);
		if((fd = ::accept(socketfd, (struct sockaddr *)&exp, &sz)) == -1){
			perror("erreur accept");
			exit(1);
		}
		std::cout << "Connexion reçue de " << &exp << std::endl;
		return Socket(fd);
	}

	void close();
};

} // ns pr
#endif /* SRC_SERVERSOCKET_H_ */
