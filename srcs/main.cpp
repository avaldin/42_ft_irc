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
#include "Channel.class.hpp"
#include <map>
#include <sstream>

int	parsingArgs(int argc, char **argv)
{
	int 				port;
	std::stringstream 	ss;

	if (argc != 3) {
		std::cerr << "Error: bad arguments" << std::endl;
		return (-1);
	}
	ss << argv[1];
	ss >> port;
	if (ss.fail()) {
		std::cerr << "Error: Bad port" << std::endl;
		return (-1);
	}
	ss.str(argv[2]);
	if (ss.str().empty()) {
		std::cerr << "Error: empty password" << std::endl;
		return (-1);
	}
	return (port);
}

int	main(int argc, char **argv)
{
	int					port;
	Server*				ircServer = Server::instantiate();

	if ((port = parsingArgs(argc, argv)) == -1)
		return (-1);
	try {ircServer->startServer(port, argv[2]);}
	catch (Exception& e) {
		e.what();
		return 1;
	}
	try {ircServer->runServer();}
	catch (Exception& e) {
		e.what();
		return 1;
	}
	return (0);
}