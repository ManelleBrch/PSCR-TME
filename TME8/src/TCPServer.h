#ifndef SRC_TCPSERVER_H_
#define SRC_TCPSERVER_H_

#include <vector>
#include <thread>
#include "ServerSocket.h"
#include "ConnectionHandler.h"

namespace pr {

// un serveur TCP, la gestion des connections est déléguée
class TCPServer {
	ServerSocket * ss; // la socket d'attente si elle est instanciee
	ConnectionHandler * handler; // le gestionnaire de session passe a la constru
	std::thread* wait_thread;
public :
	TCPServer(ConnectionHandler * handler): ss(nullptr),handler(handler), wait_thread(nullptr){}
	// Tente de creer une socket d'attente sur le port donné
	bool startServer (int port){
		ss = new ServerSocket(port);
		if(ss->isOpen()){
			//wait_thread = new std::thread(attente, this);
			//marche pas je sais pas pq

			//version avec une lambda
			wait_thread = new std::thread([](TCPServer* tcps) {
				while(true){
					Socket sc = tcps->getSS()->accept();
					if(sc.isOpen()){
						ConnectionHandler * clone = tcps->getHandler()->clone();
						clone->handleConnection(sc);
						delete clone;
					}
				}
			}, this);

		}
		return false;
	}

	ServerSocket* getSS(){
		return ss;
	}

	ConnectionHandler* getHandler(){
		return handler;
	}

	// stoppe le serveur
	void stopServer () ;
};

/*void attente(TCPServer *tcps){
	while(true){
		Socket sc = tcps->getSS()->accept();
		if(sc.isOpen()){
			ConnectionHandler * clone = tcps->getHandler()->clone();
			clone->handleConnection(sc);
			delete clone;
		}
	}
}*/

} // ns pr

#endif /* SRC_TCPSERVER_H_ */
