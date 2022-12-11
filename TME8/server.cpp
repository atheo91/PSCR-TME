#include "ServerSocket.h"
#include <iostream>
#include <winsock.h>

//programme traduit pour windows


int main00() {
	WSAData info;
	//Initialiser les socket windows
	WSAStartup(MAKEWORD(2,2),&info);

	pr::ServerSocket ss(1664);

	while (1) {
		pr::ClientSocket sc = ss.accept_connection();

		int fd = sc.getFD();

		int lu;
		recv(fd, (char *)&lu, sizeof(int), 0);
		std::cout << "lu =" << lu << std::endl;
		lu++;


		send(fd, (char *)&lu, sizeof(int), 0);
		sc.close();
	}
	ss.close();
	WSACleanup();
	return 0;
}

int main() {
	WSAData info;
	//Initialiser les socket windows
	WSAStartup(MAKEWORD(2,2),&info);

	pr::ServerSocket ss(1665);

	while (1) {
		pr::ClientSocket sc = ss.accept_connection();

		int fd = sc.getFD();

		size_t msz = sizeof(int);
		while (1) {
			int lu;
			auto nblu = recv(fd, (char *)&lu, msz, 0);
			if (nblu == 0) {
				std::cout << "Fin connexion par client" << std::endl;
				break;
			} else if (nblu < msz) {
				perror("read");
				break;
			}
			std::cout << "lu =" << lu << std::endl;

			if (lu == 0) {
				break;
			}
			lu++;
			if (send(fd, (char *)&lu, msz, 0) < msz) {
				perror("write");
				break;
			}
			std::cout << "envoyer =" << lu << std::endl;
		}
		sc.close();
	}
	WSACleanup();
	ss.close();
	return 0;
}

