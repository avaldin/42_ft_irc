/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:03:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/29 09:26:43 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.class.hpp"
#include "Server.class.hpp"
#include "Exception.class.hpp"

#include <sys/socket.h>
#include <iostream>
#include <fstream>
#include <stdio.h>

Client::Client( void ) : _clientID(0), _username("") {
	return ;
}

Client::~Client( void ) {
	return ;
}

Client::Client(int clientID, std::string username) : _clientID(clientID), _username(username) {
	return ;
}

Client::Client(Client const & src) : _clientID(src._clientID), _username(src._username) {
	*this = src;
	return ;
}

Client&	Client::operator=(Client const & rhs) {
	(void)rhs;
	return *this;
}

void	Client::action( void ) {
	char	buffer[1024];

	recv(this->_clientID, buffer, 1024, 0);
	std::cout << "buff: " << buffer << std::endl;
	Server::instanciate()->sendToServer(this->_clientID, buffer);
	return ;
}

std::string	Client::getUsername( void ) {
	return this->_username;
}

int	Client::getClientID( void ) {
	return this->_clientID;
}