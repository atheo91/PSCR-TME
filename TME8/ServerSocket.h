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

		sockaddr_in addr;
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = port;
		addr.sin_family = AF_INET;

		std::cout << "IP: " << inet_ntoa(addr.sin_addr)<<":" <<addr.sin_port<< std::endl;
		if(bind(desc_sock, (sockaddr *)&addr, sizeof(addr)) != 0){
			std::cout << "err: probleme de bind du port :" << WSAGetLastError() << std::endl;
			return;
		}
		socketfd = desc_sock;
		std::cout << socketfd<< std::endl;
	};

	int getFD() { return socketfd;}
	bool isOpen() const {return socketfd != -1;}

	ClientSocket accept_connection(){
		if(listen(socketfd, SOMAXCONN) == SOCKET_ERROR){
			std::cout << "err: Listen pas accepter : " << WSAGetLastError() <<std::endl;
			ClientSocket retour(socketfd);
			return  retour;
		}
		
		SOCKET infoSocket;
		sockaddr_in * info_ip;
		while(1){
			infoSocket = INVALID_SOCKET;
			infoSocket = accept(socketfd,NULL, NULL);
			std::cout << WSAGetLastError() << std::endl;
			if(infoSocket != INVALID_SOCKET){
				std::cout<< "trouver!"<<std::endl;
				ClientSocket retour(infoSocket);
				return  retour;
			}
		}
	}

	void close();
};

} // ns pr
#endif /* SRC_SERVERSOCKET_H_ */
