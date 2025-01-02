/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:18:47 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/02 14:51:52 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.class.hpp"
#include "Error.define.hpp"
#include "Reply.define.hpp"
#include "Server.class.hpp"
#include "Send.namespace.hpp"

#include "Client.class.hpp"

Server*	User::_server = Server::instantiate();

std::string(User::*User::_method[5])(t_data&) = {
	&User::checkRegistered,
	&User::checkParams,
	&User::checkUsernameRestriction,
	&User::checkUsernameExist,
	&User::checkNicknameExist};

User::User( void ) : _cmdName("User") {
	return ;
}

User::~User( void ) {
	return ;
}

void	User::execute(Client& client) {
	t_data		myData;
	std::string	error;

	myData.client = &client;
	for (int idx = 0; idx < 4 && !error.empty(); idx++)
		error = (this->*_method[idx])(myData);
	if (!error.empty()) {
		Send::ToClient(client._clientID, error);
		return ;
	}
	client._username = this->_username;
	if (client._nickname.empty())
		return ;
	else if (client.status == ONGOING_REGISTERING) {
		client.status = REGISTERED;
		Send::ToServer(this->_server->_serverClientId, ""); // Shity line idk this take the whole serv as argument and need to add RPL_WELCOME
	}
	return ;
}

std::string	User::checkRegistered(t_data& myData) {
	std::string	error[3] = {ERR_NOTREGISTRATED, "", ERR_ALREADYREGISTRED};
	return error[myData.client->status];
}

std::string	User::checkParams(t_data& myData) {
	(void)myData;
	if (this->_username.empty())
		return ERR_NEEDMOREPARAMS(this->_cmdName);
	return "";
}

std::string	User::checkUsernameRestriction(t_data& myData) {
	(void)myData;
	//Add a checker : 10 chara long max
	// Letters (A-Z, a-z)
	// Digits (0-9)
	// Special characters: -, ., _, and ~
	return "";
}

std::string	User::checkUsernameExist(t_data& myData) {
	(void)myData;
	//Have to add a wayto check that correctly in Server
	return "";
}

std::string	User::checkNicknameExist(t_data& myData) {
	(void)myData;
	//Have to add a wayto check that correctly in Server
	return "";
}
