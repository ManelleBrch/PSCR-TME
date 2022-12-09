#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

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

class Socket {
	int fd;

public :
	Socket():fd(-1){}
	Socket(int fd):fd(fd){}

	// tente de se connecter à l'hôte fourni
	void connect(const std::string & host, int port){
		struct addrinfo * adr;
		getaddrinfo(host.c_str(), NULL, NULL, &adr);

		in_addr ipv4 = ((sockaddr_in *)(adr->ai_addr))->sin_addr;
		freeaddrinfo(adr);
		connect(ipv4, port);

	}
	void connect(in_addr ipv4, int port){
		fd = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in adr;
		adr.sin_family = AF_INET;
		adr.sin_port = htons(port);
		adr.sin_addr = ipv4;
		if(::connect(fd, (sockaddr *)&adr, sizeof adr) == -1){
			perror("erreur connect");
			exit(1);
		}

	}

	bool isOpen() const {return fd != -1;}
	int getFD() { return fd ;}

	void close(){
		if(isOpen()){
			shutdown(fd, SHUT_RDWR);
			::close(fd);
		}
	}
};

std::ostream & operator<< (std::ostream & os, struct sockaddr_in * addr){
	char host[1024];
	if(getnameinfo((struct sockaddr *)addr, sizeof(*addr), host, sizeof(host), nullptr, 0, 0) != 0){
		perror("getnameinfo");
		exit(EXIT_FAILURE);
	}
	os << "Machine" << host << std::endl;
	os << inet_ntoa(addr->sin_addr)<< ":" << ntohs(addr->sin_port)<<std::endl;
	return os;

}

}

#endif /* SRC_SOCKET_H_ */
