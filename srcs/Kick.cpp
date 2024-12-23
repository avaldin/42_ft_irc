/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 00:42:16 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/23 20:52:14 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Kick.class.hpp"
#include "Client.class.hpp"
#include "Channel.class.hpp"
#include "Server.class.hpp"
#include "Send.namespace.hpp"
#include "Error.define.hpp"
#include "Command.class.hpp"

Server*	Kick::_server = Server::instantiate();

std::string(Kick::*Kick::_method[4])(t_data&) = {
	&Kick::checkChannelExist, 
	&Kick::checkChannelClient,
	&Kick::checkChannelOperator,
	&Kick::checkClientTargetExist};

Kick::Kick( void ) : _cmdName("KICK") {
	return ;
}

Kick::~Kick( void ) {
	return ;
}

void	Kick::execute(Client const & client) {
	t_data		myData;
	std::string	error;
	
	if (this->_targetChannels.empty() || this->_targetUsers.empty())
		error = ERR_NEEDMOREPARAMS(this->_cmdName);
	myData.client = &client;
	int const	sizeChannel = this->_targetChannels.size();
	int const	sizeUser = this->_targetUsers.size();
	for (myData.idxChannel = 0, myData.idxUser = 0; myData.idxChannel < sizeChannel && error.empty(); myData.idxChannel++) {
		for (int idx = 0; idx < 4 && error.empty(); idx++)
			error = (this->*_method[idx])(myData);
		if (!error.empty())
			Send::ToClient(client._clientID, error);
		else {
			myData.channel->deleteClient(myData.targetID);
			std::string const	message = client._prefix + " KICK " + myData.channel->_channelName + " " + this->_message;
			Send::ToChannel(*myData.channel, message);
			Send::ToClient(myData.targetID, message);
		}
		if (myData.idxUser + 1 < sizeUser)
			++myData.idxUser;
	} 
	return ;
}

std::string	Kick::checkChannelExist(t_data& myData) {
	myData.channel = this->_server->_serverChannel[this->_targetChannels[myData.idxChannel]];
	if (!myData.channel)
		return ERR_NOSUCHCHANNEL(this->_targetChannels[myData.idxChannel]);
	return "";
}

std::string	Kick::checkChannelClient(t_data& myData) {
	if (!myData.channel->isClient(myData.client->_clientID))
		return ERR_NOTONCHANNEL(myData.channel->_channelName);
	return "";
}

std::string	Kick::checkChannelOperator(t_data& myData) {
	if (!myData.channel->isOperator(myData.client->_clientID))
		return ERR_CHANOPRIVSNEEDED(myData.channel->_channelName);
	return "";
}

std::string	Kick::checkClientTargetExist(t_data& myData) {
	myData.targetUser = this->_targetUsers[myData.idxUser];
	myData.targetID = this->_server->_searchClientID[myData.targetUser->targetNickname];
	myData.targetClient = this->_server->_serverClient[myData.targetID];
	if (!myData.targetClient || !myData.channel->isClient(myData.targetID))
		return ERR_USERNOTINCHANNEL(myData.targetUser->targetNickname, myData.channel->_channelName);
	return "";
}