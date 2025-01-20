/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:03:42 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/20 13:39:12 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.class.hpp"
#include "Server.class.hpp"
#include "Exception.class.hpp"

#include <iostream>
#include <sys/socket.h>
#include <sstream>

Client::Client( void ) : _clientID(0), _username("*"), status(NOT_REGISTERED) {
	return ;
}

Client::~Client( void ) {
	return ;
}

Client::Client(int clientID) : _clientID(clientID), _username("*"), status(NOT_REGISTERED) {
	return ;
}

Client::Client(Client const & src) : _clientID(src._clientID), _nickname(src._nickname) {
	*this = src;
	return ;
}

Client&	Client::operator=(Client const & rhs) {
	(void)rhs;
	return *this;
}

Client*	Client::instantiateClient(int clientID) {
	return new Client(clientID);
}

void	Client::uninstantiateClient(Client* oldClient) {
	if (oldClient)
		delete oldClient;
	return ;
}

void	Client::action( void ) {
	char		buff[513];
	int 		bytesReceived;

	bytesReceived = recv(this->_clientID, buff, 512, 0);
	if (bytesReceived == -1)
		throw RecvException();
	else if (!bytesReceived)
	{
		_message = "QUIT :Abrupt Disconnection";
		Server::instantiate()->serverRequest(*this, _message);
		return ;
	}
	buff[bytesReceived] = '\0';
	if ((_message += buff).find('\n') != std::string::npos)
	{
		std::stringstream ss(_message);
		std::cout << "message to execut ->" << _message << std::endl;
		while (std::getline(ss, _message, '\n'))
			Server::instantiate()->serverRequest(*this, _message);
		_message = "";
	}
	return ;
}

void	Client::addChannel(std::string newChannel) {
	this->_actualChannel.push_back(newChannel);
	return ;
}

void	Client::updatePrefix( void ) {
	this->_prefix = this->_nickname + "!" + this->_username + "@" + this->localHost;
	return ;
}