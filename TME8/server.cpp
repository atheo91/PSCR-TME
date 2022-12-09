#include "ServerSocket.h"
#include <iostream>
#include <winsock.h>

int main00() {
	pr::ServerSocket ss(1664);

	while (1) {
		pr::Socket sc = ss.accept();

		int fd = sc.getFD();

		int lu;
		recv(fd, (char *)&lu, sizeof(int), 0);
		std::cout << "lu =" << lu << std::endl;
		lu++;


		send(fd, (char *)&lu, sizeof(int), 0);
		sc.close();
	}
	ss.close();
	return 0;
}

int main() {
	pr::ServerSocket ss(1664);

	while (1) {
		pr::Socket sc = ss.accept();

		int fd = sc.getFD();

		size_t msz = sizeof(int);
		while (1) {
			int lu;
			auto nblu = send(fd, (char *)&lu, msz, 0);
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
			std::cout << "envoyé =" << lu << std::endl;
		}
		sc.close();
	}

	ss.close();
	return 0;
}

