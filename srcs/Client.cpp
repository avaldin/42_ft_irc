/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:03:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/01 19:59:22 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.class.hpp"
#include "Server.class.hpp"
#include "Exception.class.hpp"

#include <sys/socket.h>
#include <iostream>
#include <fstream>
#include <stdio.h>

Client::Client( void ) : _clientID(0), _nickname("") {
	return ;
}

Client::~Client( void ) {
	return ;
}

Client::Client(int clientID, std::string nickname) : _clientID(clientID), _nickname(nickname) {
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

Client*	Client::instantiateClient(int clientID, std::string nickname) {
	return new Client(clientID, nickname);
}

void	Client::uninstantiateClient(Client* oldClient) {
	if (oldClient)
		delete oldClient;
	return ;
}

void	Client::action( void ) {
	char	buffer[1024];

	recv(this->_clientID, buffer, 1024, 0);
	std::cout << "buff: " << buffer << std::endl;
	Server::instantiate()->sendToServer(this->_clientID, buffer);
	// Server::instantiate()->serverRequest(this->_actualChannel, this->_clientID, buffer);
	return ;
}
