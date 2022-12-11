#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

//#include <netinet/ip.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iosfwd>
#include <iostream>

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
		//sortie de getaddrinfo, met les information du nom dans une structure addrinfo
		addrinfo * Iaddr; 
		int result = 0;
		//host transformer en string, et rend une stucture addrinfo  
		if(getaddrinfo(host.c_str(), NULL, NULL, &Iaddr) != 0){
			//Recupere la derniere erreur sur WinSock
			result = WSAGetLastError();
			std::cout << "err: Traduction en IPv4 rater : "<< result << std::endl;
			return;
		}

		 
		//------------- addrinfo -> sockaddr --------------
		//sockaddr est necessaire pour connecter, contient le type d'IP, l'IP et le Port du serveur
		sockaddr_in * addr;


		//Il y a plusieur adresse dans un addrinfo, on recherche un resultat en IPv4(AF_NET, et pas AF_NET6) a travers cette structure chainée
		while(Iaddr != NULL){
			if(Iaddr->ai_family== AF_INET){
				addr = (sockaddr_in *)Iaddr->ai_addr;
				addr->sin_port = port;
				addr->sin_family = Iaddr->ai_family;
			}
			Iaddr = Iaddr->ai_next;
		}

		//Info sur l'IP
		std::cout << "Nom -> IP : Traduite"<< std::endl;
		std::cout << "Nom: " << host << std::endl;
		std::cout << "IP: " << inet_ntoa(addr->sin_addr) << std::endl;
		std::cout << "Port: " << addr->sin_port << std::endl;
		std::cout << "Family: " << addr->sin_family << std::endl;

		//Libère les info collecter, on en a plus besoin.
		freeaddrinfo(Iaddr);

		//-------------- Connection aux serveur ------------
		//prend une descripteur de socket, puis sockaddr_in(qui est convertie en sockaddr) qui contient les info comme IP et PORT, pour finir sa taille
		while(1){
			if(connect(desc_sock,(sockaddr *)addr, sizeof(struct sockaddr) )!= 0){
				std::cout << "err: Connection server injoinable, essaye toutes les 5 seconds : "<< WSAGetLastError() <<std::endl;
				Sleep(5000);
			}else{
				std::cout << "Serveur trouver" << std::endl;
				break;
			}
		}

		//mise a jour du descipteur de connection
		fd = desc_sock;
	}

	void connect_server(in_addr ipv4, int port){
		/*------------- Creation du descripteur socket -----------
		La fonction socket est appeler créer le descripteur, AF_INET -> family (donc IPv4 dans notre cas), SOCK_STREAM -> type de socket (TCP dans notre cas), 
		IPPROTO_TCP -> protocole(TCP, accepte IPV4 et IPV6)*/ 

		int desc_sock;
		desc_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


		//------------- Trouver nom | in_addr(ipv4) -> nom et création de notre object sockaddr_in------------
		//sortie de getnameinfo :  prend un sockaddr qui contient une IP et retourne le nom(faut donnée la taille)
		char nom[50]; 
		int result = 0;

		sockaddr_in * addr;
		addr->sin_addr = ipv4;
		addr->sin_port = port;
		addr->sin_family = 2; //2 = IPV4 family

		if(getnameinfo((sockaddr *) addr, sizeof(addr), nom, 49,NULL,NULL,NULL) != 0){
			result = WSAGetLastError();
			std::cout << "err: Nom introuvable: "<< result << std::endl;
			return;
		}

		//Info sur l'IP
		std::cout << "Nom -> IP : Traduite"<< std::endl;
		std::cout << "Nom: " << nom << std::endl;
		std::cout << "IP: " << inet_ntoa(addr->sin_addr) << std::endl;
		std::cout << "Port: " << addr->sin_port << std::endl;
		std::cout << "Family: " << addr->sin_family << std::endl;

		//-------------- Connection aux serveur ------------
		//prend une descripteur de socket, puis sockaddr_in(qui est convertie en sockaddr) qui contient les info comme IP et PORT, pour finir sa taille
		while(1){
			if(connect(desc_sock,(sockaddr *)addr, sizeof(struct sockaddr) )!= 0){
				std::cout << "err: Connection server injoinable, essaye toutes les 5 seconds : "<< WSAGetLastError() <<std::endl;
				Sleep(5000);
			}else{
				std::cout << "Serveur trouver" << std::endl;
				break;
			}
		}

		//mise a jour du descipteur de connection
		fd = desc_sock;

	}

	bool isOpen() const {return fd != -1;}
	int getFD() { return fd ;}

	void close(){
		//shutdown est un demande de fermeture courtoise, avec la valeur SD_SEND, si cela ne marche pas on ferme violament avec closesocket
		if (shutdown(fd, SD_SEND) == SOCKET_ERROR) {
    		std::cout<< "Error, fermeture de connection : " << WSAGetLastError() << std::endl;
			closesocket(fd);
			
		}
		fd = -1;
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
