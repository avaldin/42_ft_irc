/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:03:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/02 11:02:22 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.class.hpp"
#include "Server.class.hpp"
#include "utils.hpp"
#include "Error.define.hpp"

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

Client::Client(Client const & src) : _clientID(src._clientID), _username(src._username) {
	*this = src;
	return ;
}

Client&	Client::operator=(Client const & rhs) {
	(void)rhs;
	return *this;
}

void	Client::action( void ) {
	std::string message = my_recv(this->_clientID);
	if (!this->_registered && message != "PASS" && message != "USER" && message != "NICK")
		Server::instanciate()->sendError(this->_clientID, 451, ERR_NOTREGISTRATED);
	else
		Server::instanciate()->sendToServer(this->_clientID, message);
	return ;
}

std::string	Client::getUsername( void ) const {
	return this->_username;
}

int	Client::getClientID( void ) const {
	return this->_clientID;
}

RegisterState Client::getRegistered(void) const
{
	return this->_registered;
}

void Client::setRegistered(const RegisterState registered)
{
	_registered = registered;
}

void Client::setNickname(const std::string& nickname)
{
	this->_nickname = nickname;
}

void Client::setUsername(const std::string& username)
{
	this->_username = username;
}

void Client::setRealname(const std::string& realname)
{
	this->_realname = realname;
}
