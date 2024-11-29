/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:46:54 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/29 10:11:27 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.class.hpp"
#include "Exception.class.hpp"
#include "Client.class.hpp"

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <string.h>

Server*	Server::_me = nullptr;

Server::Server( void ) {
	return ;
}

Server::~Server( void ) {
	return ;
}

Server::Server(Server const & src) {
	*this = src;
	return ;
}

Server&	Server::operator=(Server const & rhs) {
	(void)rhs;
	return  *this;
}

Server*	Server::instanciate( void ) {
	Server* singleton = new Server();
	Server* res = singleton->_me;

	singleton->_mySocket = -1;
	if (!res) {
		singleton->_me = singleton;
		return singleton;
	}
	delete singleton;
	return res;
}

void	Server::startServer(int port) {
	static sockaddr_in	address;
	
	if (this->_mySocket != -1)
		throw ServerStartException();
	this->_mySocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_mySocket == -1)
		throw SocketException();
	this->_address = &address;
	this->_port = port;
	this->_address->sin_family = AF_INET;
	this->_address->sin_addr.s_addr = INADDR_ANY;
	this->_address->sin_port = htons(port);
	this->_serverLen = sizeof(this->_address);
	if (bind(this->_mySocket, (const sockaddr *)&address, sizeof(address)) == -1)
		throw BindException();
	if (listen(this->_mySocket, 3) == -1)
		throw ListenException(); 
	this->_epollfd = epoll_create(10);
	if (this->_epollfd < 0)
		throw EpollCreateException();
	this->_ev.events = EPOLLIN;
	this->_ev.data.fd = this->_mySocket;
	if (epoll_ctl(this->_epollfd, EPOLL_CTL_ADD, this->_mySocket, &this->_ev) == -1)
		throw EpollCtlException();
	return ;
}

void	Server::runServer( void ) {
	int					nfds;
	struct epoll_event	events[10];

	std::cout << "server start running, my socket = " << this->_mySocket << std::endl;
	while (true) {
		nfds = epoll_wait(this->_epollfd, events, 10, -1);
		std::cout << "epoll received something" << std::endl;
		if (nfds == -1) 
			throw EpollWaitException();
		for (int nfd = 0; nfd < nfds; ++nfd) {
			if (events[nfd].data.fd == this->_mySocket) {
				try {this->addClient();}
				catch (Exception const & e) {
					throw AcceptException();
				}
			}
			else {
				this->_clientDatabase[events[nfd].data.fd]->action();
			}
		}
	}
}

void	Server::sendToServer(int clientID, std::string token) {
	std::string username = this->_clientDatabase[clientID]->getUsername() + ": " + token;

	std::cout << username << std::endl;
	for (std::map<int, Client *>::iterator it = this->_clientDatabase.begin(); it != this->_clientDatabase.end(); it++) {
		if (it->first != clientID) {
			int otherClient = it->second->getClientID();
			send(otherClient, username.c_str(), username.size(), 0);
		}
	}
}

void	Server::addClient() {
	struct epoll_event	event;
	int	clientID = accept(this->_mySocket, (sockaddr *)this->_address, &this->_serverLen);
	if (clientID == -1)
		throw AcceptException();
	event.data.fd = clientID;
	event.events = EPOLLIN | EPOLLPRI;             //jsp pk epollpri je l'ai pris sur internet
	std::cout << "client accepted" << std::endl;
	if (epoll_ctl(this->_epollfd, EPOLL_CTL_ADD, clientID, &event) == -1)
		throw EpollCtlException();
	Client*	newClient = new Client(clientID, "Toto");
	this->_clientDatabase[clientID] = newClient;
}

void	Server::deleteClient(int clientID) {
	delete this->_clientDatabase[clientID];
	this->_clientDatabase.erase(clientID);
	return ;	
}

sockaddr_in*	Server::getAddress( void ) {
	return this->_address;
}

int	Server::getSocketID( void ) {
	return this->_mySocket;
}

unsigned int	Server::getServerLen( void ) {
	return this->_serverLen;
}
