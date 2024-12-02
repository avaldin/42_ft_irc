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
#include "Error.define.hpp"
#include "Client.class.hpp"
#include "Channel.class.hpp"
#include <map>

int	main(int argc, char **argv)
{
	int					port;
	Server*				ircServer = Server::instantiate();

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
	return (0);
}