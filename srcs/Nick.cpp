/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 22:43:58 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/30 00:13:50 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.class.hpp"
#include "Error.define.hpp"
#include "Reply.define.hpp"
#include "Server.class.hpp"
#include "Send.namespace.hpp"

#include "Client.class.hpp"

Server*	Nick::_server = Server::instantiate();

std::string(Nick::*Nick::_method[5])(t_data&) = {
	&Nick::checkRegistered,
	&Nick::checkParams,
	&Nick::checkNicknameRestriction,
	&Nick::checkNicknameExist,
	&Nick::checkUsernameExist};

Nick::Nick( void ) : _cmdName("NICK") {
	return ;
}

Nick::~Nick( void ) {
	return ;
}

void	Nick::execute(Client& client) {
	t_data		myData;
	std::string	error;

	myData.client = &client;
	for (int idx = 0; idx < 4 && !error.empty(); idx++)
		error = (this->*_method[idx])(myData);
	if (!error.empty()) {
		Send::ToClient(client._clientID, error);
		return ;
	}
	client._nickname = this->_nickname;
	if (client._username.empty())
		return ;
	else if (client.status == ONGOING_REGISTERING) {
		client.status = REGISTERED;
		Send::ToServer(this->_server->_serverClient, ""); // Shity line idk this take the whole serv as argument and need to add RPL_WELCOME
	}
	else
		Send::ToServer(this->_server->_serverClient, client._prefix + " NICK " + this->_nickname);
	// client.updatePrefix(); new method no done yet
	return ;
}

std::string	Nick::checkRegistered(t_data& myData) {
	if (myData.client->status < ONGOING_REGISTERING)
		return ERR_NOTREGISTRATED;
	return "";
}

std::string	Nick::checkParams(t_data& myData) {
	(void)myData;
	if (this->_nickname.empty())
		return ERR_NEEDMOREPARAMS(this->_cmdName);
	return "";
}

std::string	Nick::checkNicknameRestriction(t_data& myData) {
	(void)myData;
	//Add a checker :
	// The first character must be a letter (A-Z or a-z).
	// Subsequent characters can be:
	// Letters (A-Z, a-z)
	// Digits (0-9)
	// Hyphen (-)
	// Special characters: [ ] \ ^ { }`
	return "";
}

std::string	Nick::checkNicknameExist(t_data& myData) {
	(void)myData;
	//Have to add a wayto check that correctly in Server
	return "";
}

std::string	Nick::checkUsernameExist(t_data& myData) {
	(void)myData;
	//Have to add a wayto check that correctly in Server
	return "";
}
