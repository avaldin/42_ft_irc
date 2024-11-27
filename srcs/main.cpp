#include <sys/socket.h>
#include <sys/types.h>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <csignal>
#include <iostream>
#include <cstring>

int	main(int argc, char **argv)
{
	int					serverFd, clientFd, port, serverLen;
	struct sockaddr_in	adresse;
	char				buffer[1024];

	if (argc != 3)
		return (perror("bad arguments"), -1);
	port = atoi(argv[1]);
	serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverFd == -1)
		return (perror("socket failed"), -1);
	adresse.sin_family = AF_INET;
	adresse.sin_addr.s_addr = INADDR_ANY;
	adresse.sin_port = htons(port);
	if (bind(serverFd, (const sockaddr *)&adresse, sizeof(adresse)) == -1)
		return (perror("bind failed"), close(serverFd), -1);
	if (listen(serverFd, 3) == -1)
		return (perror("listen failed"), close(serverFd), -1);
	std::cout << "listening done" << std::endl;
	serverLen = sizeof(adresse);
	clientFd = accept(serverFd, (sockaddr *)&adresse, (socklen_t *)(&serverLen));
	if (clientFd == -1)
		return (perror("Accept failed"), close(serverFd), -1);
	while (true)
	{
		std::string	message;
		memset(buffer, 0, 1024);
		std::cout << "message to client : ";
		getline(std::cin, message);
		if (message.length() == 0)
			return (close(serverFd), 0);
		send(clientFd, message.c_str(), message.length(), 0);
		send(clientFd, "enter your response : ", 23, 0);
		recv(clientFd, buffer, 1024, 0);
		std::cout << buffer << std::endl;
	}
	return (close(serverFd), 0);
}