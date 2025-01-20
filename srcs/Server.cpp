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
#include "Parser.class.hpp"
#include "Send.namespace.hpp"

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/signalfd.h>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <csignal>
#include <map>


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
//	this->_console = Factory::createClient(1);
//	this->_console->_nickname = "CONSOLE";
//	this->_console->_username = "CONSOLE";
	this->_serverPassword = password;
	signalHandler();
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
			else if (events[nfd].data.fd == this->_signalfd) {
				struct signalfd_siginfo si;
				read(_signalfd, &si, sizeof(si));
				if (si.ssi_signo == SIGINT ||si.ssi_signo == SIGQUIT || si.ssi_signo == SIGPIPE) {
					closeServer();
					_exit(0);
				}
			}
			else {
				this->_serverClientId[events[nfd].data.fd]->action();
			}
		}
	}
}

// void	Server::debugPrintServer( void ) const {
// 	std::cout << "ENTER DEBUG PRINT" << std::endl;
// 	if (this->_serverChannel.empty())
// 		return ;
// 	for (std::map<std::string, Channel*>::const_iterator it = this->_serverChannel.begin(); it != this->_serverChannel.end(); it++) {
// 		if (it->second)
// 			it->second->debugPrintChannel();
// 	}
// 	std::cout << "EXIT DEBUG PRINT" << std::endl;
// }

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
	Parser		parsed(rawLine);
	Command*	myCommand = parsed.getCommand();

	if (myCommand) {
		myCommand->execute(client);
		delete(myCommand);
		//this->debugPrintServer();
	}
	else
		Send::ToClient(client._clientID, ERR_UNKNOWNCOMMAND(client._nickname, myCommand->cmdName));
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
	event.events = EPOLLIN | EPOLLPRI;      //jsp pk epollpri je l'ai pris sur internet
	if (epoll_ctl(this->_epollfd, EPOLL_CTL_ADD, clientID, &event) == -1)
		throw EpollCtlException();
	Client*	newClient = Factory::createClient(clientID);
	newClient->localHost = inet_ntoa(this->_address->sin_addr);
	this->_serverClientId[clientID] = newClient;
}

void	Server::eraseClient(int const & clientID) {
	Client* toDelete = this->_serverClientId[clientID];
	if (epoll_ctl(_epollfd, EPOLL_CTL_DEL, clientID, nullptr) == -1)
		throw EpollCtlException();
	this->_serverClientId.erase(clientID);
	Factory::deleteClient(toDelete);
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
	std::map<int,Client*>::iterator	it = this->_serverClientId.find(id);
	if (it == this->_serverClientId.end()) 
		return NULL;
	return it->second;
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

void	Server::signalHandler() {
	sigset_t sigmask;
	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGINT);
	sigaddset(&sigmask, SIGQUIT);
	sigaddset(&sigmask, SIGPIPE);
	if (sigprocmask(SIG_BLOCK, &sigmask, NULL) != 0) {
		std::cout << "fail" << std::endl;
	}

	if ((_signalfd = signalfd(-1, &sigmask, 0)) == -1) {
		throw signalfdException();
	}

	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = _signalfd;
	if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, _signalfd, &event) == -1) {
		throw EpollCtlException();
	}
}

void	Server::closeServer() {
	for (std::map<int, Client*>::iterator it = _serverClientId.begin(); it != _serverClientId.end() ; ++it) {
		if (epoll_ctl(_epollfd, EPOLL_CTL_DEL, it->first, nullptr) == -1)
			throw EpollCtlException();
		close(it->first);
		Factory::deleteClient(it->second);
	}
	for (std::map<std::string, Channel*>::iterator it = _serverChannel.begin(); it != _serverChannel.end() ; ++it) {
		Factory::deleteChannel(it->second);
	}
	close(this->_mySocket);
	close(_epollfd);
	delete this;
}
