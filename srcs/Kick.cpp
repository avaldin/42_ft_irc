/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 00:42:16 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/15 17:33:39 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Kick.class.hpp"
#include "Client.class.hpp"
#include "Channel.class.hpp"
#include "Server.class.hpp"
#include "Send.namespace.hpp"
#include "Error.define.hpp"
#include "Command.class.hpp"

#include <iostream>

Server*	Kick::_server = Server::instantiate();

void(Kick::*Kick::_method[6])(t_data&) = {
	&Kick::checkRegistered,
	&Kick::checkParams,
	&Kick::checkChannelExist, 
	&Kick::checkChannelClient,
	&Kick::checkChannelOperator,
	&Kick::checkClientTargetExist};

void	Kick::execute(Client& client) {
	t_data		myData;

	myData.client = &client;
	for (int idx = 0; idx < 2 && myData.error.empty(); idx++)
		(this->*_method[idx])(myData);
	int const	sizeChannel = this->_targetChannels.size();
	int const	sizeUser = this->_targetUsers.size();
	std::cout << "in KICK" << std::endl;
	for (myData.idxChannel = 0, myData.idxUser = 0; myData.idxChannel < sizeChannel && myData.error.empty(); myData.idxChannel++) {
		for (int idx = 2; idx < CHECK_KICK && myData.error.empty(); idx++)
			(this->*_method[idx])(myData);
		if (myData.error.empty()) {
			myData.channel->deleteClient(myData.targetClient->_clientID);
			std::string const	message = client._prefix + " KICK " + myData.channel->_channelName + " " + this->_message;
			Send::ToChannel(*myData.channel, message);
			Send::ToClient(myData.targetClient->_clientID, message);
		}
		if (myData.idxUser + 1 < sizeUser)
			++myData.idxUser;
	}
	if (!myData.error.empty())
		Send::ToClient(client._clientID, myData.error);
	return ;
}

void	Kick::checkRegistered(t_data& myData) {
	if (myData.client->status != REGISTERED)
		myData.error = ERR_NOTREGISTRATED;
}

void	Kick::checkParams(t_data& myData) {
	if (this->_targetChannels.empty() || this->_targetUsers.empty())
		myData.error =  ERR_NEEDMOREPARAMS(this->_cmdName);
}

void	Kick::checkChannelExist(t_data& myData) {
	std::map<std::string, Channel*>::iterator it = this->_server->_serverChannel.find(this->_targetChannels[myData.idxChannel]);
	
	if (it == this->_server->_serverChannel.end())
		myData.error =  ERR_NOSUCHCHANNEL(this->_targetChannels[myData.idxChannel]);
	myData.channel = it->second;
	return ;
}

void	Kick::checkChannelClient(t_data& myData) {
	if (!myData.channel->isClient(myData.client->_clientID))
		myData.error = ERR_NOTONCHANNEL(myData.channel->_channelName);
}

void	Kick::checkChannelOperator(t_data& myData) {
	if (!myData.channel->isOperator(myData.client->_clientID))
		myData.error = ERR_CHANOPRIVSNEEDED(myData.channel->_channelName);
}

void	Kick::checkClientTargetExist(t_data& myData) {
	myData.targetUser = this->_targetUsers[myData.idxUser];
	myData.targetClient = this->_server->findClientNickname(myData.targetUser);
	if (!myData.targetClient || !myData.channel->isClient(myData.targetClient->_clientID))
		myData.error =  ERR_USERNOTINCHANNEL(myData.targetUser, myData.channel->_channelName);
}
 