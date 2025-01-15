/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 22:43:58 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/13 17:19:50 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.class.hpp"
#include "Error.define.hpp"
#include "Reply.define.hpp"
#include "Server.class.hpp"
#include "Send.namespace.hpp"

#include "Client.class.hpp"

#include "iostream"

Server*	Nick::_server = Server::instantiate();

void(Nick::*Nick::_method[4])(t_data&) = {
	&Nick::checkRegistered,
	&Nick::checkParams,
	&Nick::checkNicknameRestriction,
	&Nick::checkNicknameExist};

Nick::Nick( void ) : _cmdName("NICK") {
	return ;
}

Nick::~Nick( void ) {
	return ;
}

void	Nick::execute(Client& client) {
	t_data		myData;

	myData.client = &client;
	for (int idx = 0; idx < 4 && myData.error.empty(); idx++)
		(this->*_method[idx])(myData);
	if (!myData.error.empty()) {
		Send::ToClient(client._clientID, myData.error);
		return ;
	}
	client._nickname = this->_nickname;
	client.updatePrefix();
	if (!client._username.compare("*"))
		return ;
	else if (client.status == ONGOING_REGISTERING) {
		client.status = REGISTERED;
		Send::ToServer(this->_server->_serverClientId, RPL_WELCOME(client._nickname));
	}
	else
		Send::ToServer(this->_server->_serverClientId, client._prefix + " NICK " + this->_nickname);
	return ;
}

void	Nick::checkRegistered(t_data& myData) {
	if (myData.client->status < ONGOING_REGISTERING)
		myData.error = ERR_NOTREGISTRATED(myData.client->_nickname);
	return ;
}

void	Nick::checkParams(t_data& myData) {
	if (this->_nickname.empty())
		myData.error = ERR_NEEDMOREPARAMS(myData.client->_nickname, this->_cmdName);
	return ;
}

static bool	checkCorpus(char c) {
	char uniqueChar[7] = "-[]^{}";
	 
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' &&  c <= 'z') || (c >= '0' && c <= '9'))
		return true;
	for (int idx = 0; idx < 7; idx++) {
		if (uniqueChar[idx] == c)
			return true;
	}
	return false;
}

void	Nick::checkNicknameRestriction(t_data& myData) {
	int const	size = this->_nickname.size();

	if (size > 9 || size == 0 || !((this->_nickname[0] >= 'A' && this->_nickname[0] <= 'Z') 
								|| (this->_nickname[0] >= 'a' &&  this->_nickname[0] <= 'z')))
		myData.error = ERR_ERRONEUSNICKNAME(myData.client->_nickname, this->_nickname);
	for (int idx = 0; idx < size; idx++) {
		if (!checkCorpus(this->_nickname[idx]))
			myData.error = ERR_ERRONEUSNICKNAME(myData.client->_nickname, this->_nickname);
	}
	return ;
}

void	Nick::checkNicknameExist(t_data& myData) {
	if (this->_server->findClientNickname(this->_nickname))
		myData.error = ERR_NICKCOLLISION(myData.client->_nickname, this->_nickname);
	return ;
}
