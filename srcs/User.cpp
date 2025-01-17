/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:18:47 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/17 11:54:26 by avaldin          ###   ########.fr       */
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
	if (client._nickname.empty())
		return ;
	else if (client.status == ONGOING_REGISTERING) {
		client.status = REGISTERED;
		Send::ToServer(this->_server->_serverClientId, RPL_WELCOME(client._nickname)); // Shity line idk this take the whole serv as argument and need to add RPL_WELCOME
	}
	return ;
}

void	User::checkRegistered(t_data& myData) {
	std::string	error[3] = {ERR_NOTREGISTRATED(myData.client->_nickname), "", ERR_ALREADYREGISTRED(myData.client->_nickname)};
	myData.error = error[myData.client->status];
	return ;
}

void	User::checkParams(t_data& myData) {
	if (this->_username.empty() || this->_mode.empty() || this->_realname.empty())
		myData.error = ERR_NEEDMOREPARAMS(myData.client->_nickname, this->_cmdName);
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

	if (this->_username.length() > 10)
		this->_username.resize(10);
	for (unsigned long idx= 0; idx < this->_username.length(); idx++) {
		if (!checkCorpus(this->_username[idx]))
			this->_username[idx] = 'A';
	}
	return ;
}

void	User::checkModeExist(t_data& myData) {
	if (this->_mode.compare("0"))
		myData.error = ERR_UMODEUNKNOWNFLAG(myData.client->_nickname, this->_mode); //idk if needed
	return ;
}
