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
	std::thread wait_thread;
public :
	TCPServer(ConnectionHandler * handler): ss(nullptr),handler(handler) {}
	// Tente de creer une socket d'attente sur le port donné
	bool startServer (int port){
		ss = new ServerSocket(port);
		if(ss->isOpen()){
			while(true){
				Socket sc = ss->accept();
				if(sc.isOpen()){
					ConnectionHandler * clone = handler->clone();
					threads.emplace_back(clone->handleConnection,sc);
				}
			}
		}
		return false;
	}

	// stoppe le serveur
	void stopServer () ;
};

} // ns pr

#endif /* SRC_TCPSERVER_H_ */
