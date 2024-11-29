#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <csignal>
#include <iostream>
#include <cstring>
#include "Server.class.hpp"
#include "Exception.class.hpp"
#include "Client.class.hpp"
#include <map>

int	main(int argc, char **argv)
{
	int					port;
	Server*				ircServer = Server::instanciate();

	if (argc != 2)
		return (perror("bad arguments"), -1);
	port = atoi(argv[1]);
	try {ircServer->startServer(port);}
	catch (Exception& e) {
		e.what();
		return 1;
	}
	try {ircServer->runServer();}
	catch (Exception& e) {
		e.what();
		return 1;
	}
	// clientFd = accept(ircServer->getSocketID(), (sockaddr *)ircServer->getAddress(), (socklen_t *)ircServer->getServerLen());
	// if (clientFd == -1)
	// 	return (perror("Accept failed"), close(ircServer->getSocketID()), -1);
	// while (true)
	// {
	// 	std::string	message;
	// 	memset(buffer, 0, 1024);
	// 	std::cout << "message to client: ";
	// 	getline(std::cin, message);
	// 	if (message.length() == 0)
	// 		return (close(ircServer->getSocketID()), 0);
	// 	send(clientFd, message.c_str(), message.length(), 0);
	// 	send(clientFd, "\nenter your response: ", 23, 0);
	// 	recv(clientFd, buffer, 1024, 0);
	// 	std::cout << buffer;
	// }
	return (close(ircServer->getSocketID()), 0);
}