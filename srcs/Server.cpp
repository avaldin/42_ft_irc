/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:46:54 by tmouche           #+#    #+#             */

/*   Updated: 2025/01/11 19:33:11 by tmouche          ###   ########.fr       */
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
#include <cstring>
#include <sstream>
#include <ctime>

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

void	Server::startServer(int port, const std::string& password) {
	static sockaddr_in	address;
	
	if (this->_mySocket != -1)
		throw ServerStartException();
	this->_mySocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_mySocket == -1)
		throw SocketException();
	int opt = 1;
	if (setsockopt(this->_mySocket,SOL_SOCKET, SO_REUSEADDR, &opt,  sizeof(opt)) == -1)
		throw setsockoptException();
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
	this->_serverPassword = password;
	return ;
}

void	Server::runServer( void ) {
	int					nfds;
	struct epoll_event	events[10];

	while (true) {
		nfds = epoll_wait(this->_epollfd, events, 10, -1);
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
				this->_serverClientId[events[nfd].data.fd]->action();
			}
		}
	}
}

void	Server::debugPrintServer( void ) const {
	std::cout << "ENTER DEBUG PRINT" << std::endl;
	if (this->_serverChannel.empty())
		return ;
	for (std::map<std::string, Channel*>::const_iterator it = this->_serverChannel.begin(); it != this->_serverChannel.end(); it++) {
		if (it->second)
			it->second->debugPrintChannel();
	}
	std::cout << "EXIT DEBUG PRINT" << std::endl;
}

// void	Server::LegacysendToServer(int const clientID, std::string token) {
// 	std::string nickname = this->_serverClientId[clientID]->_nickname + ": " + token;
// 	std::cout << nickname << std::endl;
// 	for (std::map<int const &, Client *>::iterator it = this->_serverClientId.begin(); it != this->_serverClientId.end(); it++) {
// 		int otherClient = it->second->_clientID;
// 		send(otherClient, nickname.c_str(), nickname.size(), 0);
// 	}
// }

// void	Server::LegacysendToChannel(std::string const channelName, int const clientID, std::string token) {
// 	std::string	line;

// 	if (this->_serverChannel[channelName]->isOperator(clientID))
// 		line += "@";
// 	line += (this->_serverClientId[clientID]->_nickname + ": " + token);
// 	this->_serverChannel[channelName]->sendToChannel(line);
// 	return ;
// }

void	Server::serverRequest(Client& client, std::string rawLine) {
	std::string	const	logLine = ":" + client._nickname + "!" + client._username + "@" + this->_serverName + " " + rawLine; 
	
	// Send::ToConsole(client._clientID, logLine);
	Command		myCommand(rawLine);
	if (myCommand._command) {
		myCommand._command->execute(client);
		this->debugPrintServer();
	}
	else
		Send::ToClient(client._clientID, ERR_UNKNOWNCOMMAND(client._nickname, myCommand._cmdName));
	return ;
}

// void	Server::processCommand(ACommand* command) {
// 	command->execute();
// 	return ;
// }

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
	event.events = EPOLLIN | EPOLLPRI;      //jsp pk epollpri je l'ai pris sur internet
	if (epoll_ctl(this->_epollfd, EPOLL_CTL_ADD, clientID, &event) == -1)
		throw EpollCtlException();
	Client*	newClient = Factory::createClient(clientID);
	this->_serverClientId[clientID] = newClient;
}

void	Server::eraseClient(int const & clientID) {
	this->_serverClientId.erase(clientID);
	Factory::deleteClient(this->_serverClientId[clientID]);
	return ;	
}

Client*	Server::findClientUsername(std::string const & username) {
	for (std::map<int, Client*>::iterator it = this->_serverClientId.begin(); it != this->_serverClientId.end(); it++) {
		if (!it->second->_username.compare(username))
			return it->second;
	}
	return NULL;
}

Client*	Server::findClientNickname(std::string const & nickname) {
	for (std::map<int, Client*>::iterator it = this->_serverClientId.begin(); it != this->_serverClientId.end(); it++) {
		if (!it->second->_nickname.compare(nickname))
			return it->second;
	}
	return NULL;
}

Client*	Server::findClientId(int const & id) {
	return this->_serverClientId[id];
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
