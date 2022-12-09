#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

//#include <netinet/ip.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include <iosfwd>
#include <iostream>

namespace pr {

class Socket {
	int fd;

public :
	Socket():fd(-1){}
	Socket(int fd):fd(fd){}

	// tente de se connecter à l'hôte fourni
	void connect_server(const std::string & host, int port){
		
		/*--Creation du descripteur socket--
		La fonction socket est appeler créer le descripteur, AF_INET -> family (donc IPv4 dans notre cas), SOCK_STREAM -> type de socket (TCP dans notre cas), 
		IPPROTO_TCP -> protocole(TCP, accepte IPV4 et IPV6)*/ 

		SOCKET desc_sock;
		desc_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		//--Traduction Nom -> addrinfo
		//structure sortie de getaddrinfo, 
		struct addrinfo * Iaddr; 
		getaddrinfo(host.c_str(), NULL, NULL, &Iaddr);//host transformer en string, et rend une stucture addrinfo  

		if(Iaddr->ai_family != AF_INET){
			std::cout << "err: Pas IPv4"<< std::endl;
			return;
		}

		struct sockaddr * addr = Iaddr->ai_addr;

		//connection aux serveur, prend une descripteur de socket, puis sockaddr_in qui contient les info comme IP et PORT, pour finir sa taille
		if(connect(desc_sock,addr, sizeof(struct sockaddr) )!= 0){
			std::cout << "err: Connection server injoinable"<< std::endl;
		}
		std::cout << "ADDR INFO : " << *addr->ai_addr->sa_data << std::endl;

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
}

}
#endif /* SRC_SOCKET_H_ */
