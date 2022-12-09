#include "ServerSocket.h"
//#include <unistd.h>
#include <string>
#include <iostream>

int main00() {
	pr::Socket sock;
	sock.connect_server("localhost", 1664);
	int N=42;
	send(sock.getFD(),(char *)&N,sizeof(int), 0);
	recv(sock.getFD(),(char *)&N,sizeof(int),0);
	std::cout << N << std::endl;
	return 0;
}


// avec controle
int main0() {

	pr::Socket sock;

	sock.connect_server("localhost", 1664);

	if (sock.isOpen()) {
		int fd = sock.getFD();
		int i = 10;
		size_t msz = sizeof(int);
		if (send(fd,(char *) &i, msz,0) < msz) {
			perror("write");
		}
		std::cout << "envoyé =" << i << std::endl;
		int lu;
		auto nblu = recv(fd, (char *)&lu, msz,0);
		if (nblu == 0) {
			std::cout << "Fin connexion par serveur" << std::endl;
		} else if (nblu < msz) {
			perror("read");
		}
		std::cout << "lu =" << lu << std::endl;
	}

	return 0;
}


// avec une boucle, on attend un 0
int main() {

	pr::Socket sock;

	sock.connect_server("localhost", 1664);

	if (sock.isOpen()) {
		int fd = sock.getFD();

		size_t msz = sizeof(int);
		for (int i = 10; i >= 0; i--) {
			if (send(fd,(char *) &i, msz,0) < msz) {
				perror("write");
				break;
			}
			std::cout << "envoyé =" << i << std::endl;

			int lu;
			auto nblu = recv(fd, (char *)&lu, msz,0);
			if (nblu == 0) {
				std::cout << "Fin connexion par serveur" << std::endl;
				break;
			} else if (nblu < msz) {
				perror("read");
				break;
			}
			std::cout << "lu =" << lu << std::endl;
		}
	}

	return 0;
}

