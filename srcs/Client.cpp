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
#include "utils.hpp"

#include <iostream>

Client::Client( void ) : _clientID(0), _username("*") {
	return ;
}

Client::~Client( void ) {
	return ;
}

Client::Client(int clientID) : _clientID(clientID), _username("*") {
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
	std::string message = my_recv(this->_clientID);
	Server::instanciate()->sendToServer(this->_clientID, message);
	return ;
}
