#ifndef SRC_SERVERSOCKET_H_
#define SRC_SERVERSOCKET_H_

#include "ClientSocket.h"

namespace pr {

class ServerSocket {
	int socketfd;

public :
	// Demarre l'ecoute sur le port donne
	ServerSocket(int port){
		
		/*------------- Creation du descripteur socket -----------
		La fonction socket est appeler créer le descripteur, AF_INET -> family (donc IPv4 dans notre cas), SOCK_STREAM -> type de socket (TCP dans notre cas), 
		IPPROTO_TCP -> protocole(TCP, accepte IPV4 et IPV6)*/ 

		int desc_sock;
		desc_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		//--------------- Création du sockaddr, contenant les IP accepter, le port, et le type(IPv4) ----------------------------
		sockaddr_in addr;
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = port;
		addr.sin_family = AF_INET;
		std::cout << "IP(Port): " << inet_ntoa(addr.sin_addr)<<":" <<addr.sin_port<< std::endl;

		//----------------Liaison avec le serveur et le port affecter --------------
		if(bind(desc_sock, (sockaddr *)&addr, sizeof(addr)) != 0){
			std::cout << "err: probleme de bind du port :" << WSAGetLastError() << std::endl;
			socketfd = -1;
			return;
		}

		//Descripteur est mis à jours, maintenant lier au port.
		socketfd = desc_sock;
		//std::cout << socketfd<< std::endl;
	};

	int getFD() { return socketfd;}
	bool isOpen() const {return socketfd != -1;}

	ClientSocket accept_connection(){
		// ------------- Ecoute des client ----------
		//Listen permet d'écouter SOMAXCONN de personne parlant a ce programme
		if(listen(socketfd, SOMAXCONN) == SOCKET_ERROR){
			std::cout << "err: Listen pas accepter : " << WSAGetLastError() <<std::endl;
			ClientSocket retour(socketfd);
			return  retour;
		}
		
		// ------------- Trie des message reçu --------
		//Accept vérifie que si le programme reçoit un message, il parle au bon port. Si c'est le mauvais port, le message est ignorer, peut récupérer les info client
		SOCKET infoSocket;
		while(1){
			infoSocket = INVALID_SOCKET;
			infoSocket = accept(socketfd,NULL, NULL);
			std::cout << WSAGetLastError() << std::endl;
			if(infoSocket != INVALID_SOCKET){
				std::cout<< "Trouver client!"<<std::endl;
				ClientSocket retour(infoSocket);
				return  retour;
			}
		}
	}

	void close(){
		//shutdown est un demande de fermeture courtoise, avec la valeur SD_SEND, si cela ne marche pas on ferme violament avec closesocket
		if (shutdown(socketfd, SD_SEND) == SOCKET_ERROR) {
    		std::cout<< "Error, fermeture de connection : " << WSAGetLastError() << std::endl;
			closesocket(socketfd);
		}
		socketfd = -1;
	}
};

} // ns pr
#endif /* SRC_SERVERSOCKET_H_ */
