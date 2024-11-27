/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:46:54 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/27 21:01:26 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.class.hpp"
#include "Exception.class.hpp"

	Server*	Server::_me = nullptr;

Server::Server( void )  {
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

void	Server::startServer(int port) {
	this->_mySocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_mySocket == -1)
		throw SocketException();
	this->_port = port;
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_port = htons(port);
	if (bind(this->_mySocket, (const sockaddr *)&this->_address, sizeof(this->_address)) == -1)
		throw BindException();
	if (listen(this->_mySocket, 3) == -1)
		throw ListenException(); 
	return ;
}

Server*	Server::instanciate( void ) {
	Server* singleton = new Server();
	Server* res = singleton->_me;

	if (!res) {
		singleton->_me = singleton;
		return singleton;
	}
	delete singleton;
	return res;
}

struct sockaddr_in*	Server::getAddress( void ) {
	return &this->_address;
}

int	Server::getSocketID( void ) {
	return this->_mySocket;
}
