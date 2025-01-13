/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:18:47 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/08 18:07:42 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "User.class.hpp"
#include "Error.define.hpp"
#include "Reply.define.hpp"
#include "Server.class.hpp"
#include "Send.namespace.hpp"

#include "Client.class.hpp"

Server*	User::_server = Server::instantiate();

void(User::*User::_method[NB_CHECK])(t_data&) = {
	&User::checkRegistered,
	&User::checkParams,
	&User::checkUsernameRestriction,
	&User::checkModeExist};

User::User( void ) : _cmdName("User") {
	return ;
}

User::~User( void ) {
	return ;
}

void	User::execute(Client& client) {
	t_data		myData;

	myData.client = &client;
	for (int idx = 0; idx < NB_CHECK && myData.error.empty(); idx++)
		(this->*_method[idx])(myData);
	if (!myData.error.empty()) {
		Send::ToClient(client._clientID, myData.error);
		return ;
	}
	client._username = this->_username;
	client.updatePrefix();
	std::cout << "bef nick status" << std::endl;
	if (client._nickname.empty())
		return ;
	else if (client.status == ONGOING_REGISTERING) {
		client.status = REGISTERED;
		Send::ToServer(this->_server->_serverClientId, RPL_WELCOME(client._prefix)); // Shity line idk this take the whole serv as argument and need to add RPL_WELCOME
	}
	return ;
}

void	User::checkRegistered(t_data& myData) {
	std::string	error[3] = {ERR_NOTREGISTRATED, "", ERR_ALREADYREGISTRED};
	myData.error = error[myData.client->status];
	return ;
}

void	User::checkParams(t_data& myData) {
	if (this->_username.empty() || this->_mode.empty() || this->_realname.empty())
		myData.error = ERR_NEEDMOREPARAMS(this->_cmdName);
	return ;
}

static bool	checkCorpus(char c) {
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' &&  c <= 'z') || (c >= '0' && c <= '9')
		|| c == '-' || c == '.' || c == '_' || c == '~' || c == 0)
		return true;
	return false;
}

void	User::checkUsernameRestriction(t_data& myData) {
	(void)myData;

	this->_username.resize(10);
	for (int idx= 0; idx < 10; idx++) {
		if (!checkCorpus(this->_username[idx]))
			this->_username[idx] = 'A';
	}
	return ;
}

void	User::checkModeExist(t_data& myData) {
	if (this->_mode.compare("0"))
		myData.error = ERR_UMODEUNKNOWNFLAG;
	return ;
}
