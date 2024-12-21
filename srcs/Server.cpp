/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:46:54 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/21 02:18:58 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.class.hpp"
#include "Exception.class.hpp"
#include "Client.class.hpp"
#include "Channel.class.hpp"
#include "Error.define.hpp"
#include "Command.class.hpp"
#include "Send.namespace.hpp"

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <string.h>
#include <sstream>

Server*	Server::_me = nullptr;

Server::Server( void ) : _serverName("irc.serv") {
	return ;
}

Server::~Server( void ) {
	return ;
}

Server*	Server::instantiate( void ) {
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
	this->_console = Factory::createClient(1);
	this->_console->_nickname = "CONSOLE";
	this->_console->_username = "CONSOLE";
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
				this->_serverClient[events[nfd].data.fd]->action();
			}
		}
	}
}

void	Server::LegacysendToServer(int const clientID, std::string token) {
	std::string nickname = this->_serverClient[clientID]->_nickname + ": " + token;

	std::cout << nickname << std::endl;
	for (std::map<int, Client *>::iterator it = this->_serverClient.begin(); it != this->_serverClient.end(); it++) {
		int otherClient = it->second->_clientID;
		send(otherClient, nickname.c_str(), nickname.size(), 0);
	}
}

void	Server::LegacysendToChannel(std::string const channelName, int const clientID, std::string token) {
	std::string	line;

	if (this->_serverChannel[channelName]->isOperator(clientID))
		line += "@";
	line += (this->_serverClient[clientID]->_nickname + ": " + token);
	this->_serverChannel[channelName]->sendToChannel(line);
	return ;
}

void	Server::serverRequest(int clientID, std::string rawLine) {
	Client	*currentClient = this->_serverClient[clientID];
	if (!currentClient)
		return ;// throw BIG ERROR, make non sense if this append
	std::string	const	logLine = ":" + currentClient->_nickname + "!" + currentClient->_username + "@" + this->_serverName + " " + rawLine; 
	
	Send::ToConsole(clientID, logLine);
	Command		myCommand(rawLine);
	processCommand(&myCommand);
	return ;
}

void	Server::processCommand(Command* command) {
	(void)command;
	return ;
}

void	Server::addChannel(t_channelType channelType, std::string channelName) {
	Channel*	newChannel = Factory::createChannel(channelType, channelName);
	this->_serverChannel[channelName] = newChannel;
	return ;
}

void	Server::eraseChannel(std::string channelName) {
	Factory::deleteChannel(this->_serverChannel[channelName]);
	this->_serverChannel.erase(channelName);
	return ;
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
	Client*	newClient = Factory::createClient(clientID);
	this->_serverClient[clientID] = newClient;
}

void	Server::eraseClient(int clientID) {
	Factory::deleteClient(this->_serverClient[clientID]);
	this->_serverClient.erase(clientID);
	return ;	
}

// SUBCLASS FACTORY //

Server::Factory::Factory( void ) {
	return ;
}

Server::Factory::~Factory( void ) {
	return ;
}

Client*	Server::Factory::createClient(int clientID) {
	return (Client::instantiateClient(clientID));
}

void	Server::Factory::deleteClient(Client* oldClient) {
	Client::uninstantiateClient(oldClient);
	return ;
}

Channel*	Server::Factory::createChannel(t_channelType channelType, std::string channelName) {
	return (Channel::instantiateChannel(channelType, channelName));	
}

void	Server::Factory::deleteChannel(Channel* oldChannel) {
	Channel::uninstantiateChannel(oldChannel);
	return ;
}

void	Server::sendError(int const clientId, std::string const & msgError)
{
	if (send(clientId, msgError.c_str(), msgError.size(), 0) == -1)
		throw SendException();
	return ;
}
