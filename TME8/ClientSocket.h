#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

//#include <netinet/ip.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iosfwd>
#include <iostream>
#include <chrono>

namespace pr {

class ClientSocket {
	int fd;

public :
	ClientSocket():fd(-1){}
	ClientSocket(SOCKET fd):fd(fd){}

	// tente de se connecter au nom de l'hôte fourni
	void connect_server(const std::string & host, int port){

		/*------------- Creation du descripteur socket -----------
		La fonction socket est appeler créer le descripteur, AF_INET -> family (donc IPv4 dans notre cas), SOCK_STREAM -> type de socket (TCP dans notre cas), 
		IPPROTO_TCP -> protocole(TCP, accepte IPV4 et IPV6)*/ 

		int desc_sock;
		desc_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


		//------------- Traduction | Nom -> addrinfo ------------
		//structure sortie de getaddrinfo, 
		addrinfo * Iaddr; 
		int result = 0;
		//host transformer en string, et rend une stucture addrinfo  
		if(getaddrinfo(host.c_str(), NULL, NULL, &Iaddr) != 0){
			//Recupere la derniere erreur sur WinSock
			result = WSAGetLastError();
			std::cout << "err: Traduction en IPv4 rater."<< std::endl;
			std::cout << result << std::endl;
			return;
		}

		 
		//------------- addrinfo -> sockaddr --------------
		//sockaddr est necessaire pour connecter, contient le type d'IP, l'IP et le Port du serveur
		sockaddr_in * addr;

		while(Iaddr->ai_next != NULL){
			std::cout << "c" << std::endl;
			if(Iaddr->ai_family== AF_INET6){
				std::cout << "c" << std::endl;
				 addr = (sockaddr_in *)Iaddr->ai_addr;
			}
			std::cout << "c" << std::endl;
			Iaddr = Iaddr->ai_next;
			std::cout << "c" << std::endl;
		}
		
std::cout << "c" << addr->sin_family << std::endl;
		addr->sin_addr.s_addr = inet_addr("127.0.0.1");
		addr->sin_port = port;
		addr->sin_family = 2;
	    freeaddrinfo(Iaddr);

		//Info sur l'IP
		std::cout << "Nom -> IP : Traduite"<< std::endl;
		std::cout << "IP: " << inet_ntoa(addr->sin_addr) << std::endl;
		std::cout << "Port: " << addr->sin_port << std::endl;
		std::cout << "Family: " << addr->sin_family << std::endl;

		//-------------- Connection aux serveur ------------
		//prend une descripteur de socket, puis sockaddr_in qui contient les info comme IP et PORT, pour finir sa taille
		while(1){
			if(connect(desc_sock,(sockaddr *)addr, sizeof(struct sockaddr) )!= 0){
				std::cout << "err: Connection server injoinable, essaye toutes les 5 seconds : "<< WSAGetLastError() <<std::endl;
				Sleep(5000);
			}else{
				std::cout << "Serveur trouvé" << std::endl;
				break;
			}
		}

		fd = desc_sock;

	}
	void connect_server(in_addr ipv4, int port){
	
	}

	bool isOpen() const {return fd != -1;}
	int getFD() { return fd ;}

	void close(){

	};
};

std::ostream & operator<< (std::ostream & os, struct sockaddr_in * addr){
	char host[1024];
	//recherche DNS avec l'addresse, qui retourne le nom de l'addresse
	getnameinfo((struct sockaddr *) addr, sizeof(struct sockaddr *),host, 1023, NULL, 0,0);
	os << "Machine" << host << std::endl;
	os << inet_ntoa(addr->sin_addr) << ":" << ntohs(addr->sin_port) << std::endl;
	return os;
}

}
#endif /* SRC_SOCKET_H_ */
