/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:01:25 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/20 16:37:36 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.class.hpp"

#include "Error.define.hpp"
#include "Reply.define.hpp"

#include "Send.namespace.hpp"

#include "Server.class.hpp"
#include "Client.class.hpp"
#include "Channel.class.hpp"

#include <cstdio>
#include <iostream>

Server*	Join::_server = Server::instantiate();

void(Join::*Join::_method[CHECK_JOIN])(t_data&) = {
	&Join::checkRegistered,
	&Join::checkParams,
	&Join::checkChannelName,
	&Join::checkChannelExist,
	&Join::checkChannelKey,
	&Join::checkChannelInvite,
	&Join::checkChannelFilling};

void	Join::execute(Client& client) {
	t_data	myData;
	int		idx;

	myData.client = &client;
	for (idx = 0; idx < 2 && myData.error.empty(); idx++)// attention au 2
		(this->*_method[idx])(myData);
	if (!myData.error.empty()) {
		Send::ToClient(client._clientID, myData.error);
		return ;
	}
	int const sizeChannels = this->_targetChannels.size();
	myData.sizeKey = this->_targetKeys.size();
	myData.idxKey = 0;
	for (int idxChannel = 0; idxChannel < sizeChannels && myData.error.empty(); idxChannel++, myData.idxKey++) {
		myData.targetName = this->_targetChannels[idxChannel];
		for (int idxCheck = idx; idxCheck < idx + 2 && myData.error.empty(); idxCheck++)
			(this->*_method[idx])(myData);
		if (myData.error.empty() && myData.targetChannel)
			joinChannel(myData);
		else if (myData.error.empty())
			createChannel(myData);
		if (!myData.error.empty())
			Send::ToClient(client._clientID, myData.error);
		else
			RPL_join(myData);
		myData.error.clear();
		myData.targetKey.clear();
		myData.targetChannel = NULL;
	}
	return ;
}

void	Join::RPL_join(t_data& myData) {
	Send::ToChannel(*myData.targetChannel, ":" + myData.client->_nickname + "!" + myData.client->_username + "@" + myData.client->localHost + " JOIN :" + myData.targetChannel->_channelName);
	if (!myData.targetChannel->_channelTopic.empty())
		Send::ToClient(myData.client->_clientID, RPL_TOPIC(myData.client->_nickname, myData.targetChannel->_channelName ,myData.targetChannel->_channelTopic));
	else
		Send::ToClient(myData.client->_clientID, RPL_NOTOPIC(myData.client->_nickname, myData.targetChannel->_channelName));
	std::string	names;
	for (std::map<int, Client const *>::iterator it = myData.targetChannel->_channelClient.begin(); it != myData.targetChannel->_channelClient.end() ; ++it) {
		if (myData.targetChannel->isOperator(it->first))
			names += "@";
		names += it->second->_nickname + " ";
	}
	names.erase(names.size() - 1);
	Send::ToClient(myData.client->_clientID, RPL_NAMERPLY(myData.client->_nickname, myData.targetChannel->_channelName, names));
	Send::ToClient(myData.client->_clientID, RPL_ENDOFNAMES(myData.client->_nickname, myData.targetChannel->_channelName));
}

void	Join::joinChannel(t_data& myData) {
	if (myData.idxKey < myData.sizeKey)
		myData.targetKey = this->_targetKeys[myData.idxKey];
	for (int idx = 3;idx < CHECK_JOIN && myData.error.empty(); idx++)
		(this->*_method[idx])(myData);
	if (!myData.error.empty())
		return ;
	myData.targetChannel->addClient(myData.client->_clientID, myData.client);
	return ;
}

void	Join::createChannel(t_data& myData) {
	this->_server->addChannel(MODE, myData.targetName);
	myData.targetChannel = this->_server->_serverChannel[myData.targetName];
	myData.targetChannel->addClient(myData.client->_clientID, myData.client);
	myData.targetChannel->addOperator(myData.client->_clientID);
	if (myData.idxKey < myData.sizeKey)
		myData.targetChannel->_channelPassword = this->_targetKeys[myData.idxKey];
	return ;
}

void	Join::checkRegistered(t_data& myData) {
	if (myData.client->status != REGISTERED)
		myData.error = ERR_NOTREGISTRATED(myData.client->_nickname);
	return ;
}

void	Join::checkParams(t_data& myData) {
	if (this->_targetChannels.empty())
		myData.error = ERR_NEEDMOREPARAMS(myData.client->_nickname, this->_cmdName);
	return ;
}

void	Join::checkChannelName(t_data& myData) {
	int const size = myData.targetName.size();
	
	if (size > 50 || myData.targetName[0] != '&')
		myData.error = ERR_BADCHANMASK(myData.client->_nickname, myData.targetName);
	for (int idx = 0; idx < size && myData.error.empty(); idx++) {
		char const	c = myData.targetName[idx]; 
		if (c <= 32 || c == ',' || c == ':')
			myData.error = ERR_BADCHANMASK(myData.client->_nickname, myData.targetName);
	}
	return ;
}

void	Join::checkChannelExist(t_data& myData) {
	std::map<std::string,Channel*>::iterator	it = this->_server->_serverChannel.find(myData.targetName); 
	
	myData.targetChannel = NULL;
	if (it != this->_server->_serverChannel.end())
		myData.targetChannel == it->second;
	return ;
}

void	Join::checkChannelKey(t_data& myData) {
	if (!myData.targetChannel->_channelPassword.empty() && myData.targetKey.compare(myData.targetChannel->_channelPassword)) {
		myData.error = ERR_BADCHANNELKEY(myData.client->_nickname, myData.targetChannel->_channelName);
	}
	return ;
}

void	Join::checkChannelInvite(t_data& myData) {
	if (myData.targetChannel->_inviteOnlyMode && !myData.targetChannel->isInvited(myData.client->_clientID))
		myData.error = ERR_INVITEONLYCHAN(myData.client->_nickname, myData.targetChannel->_channelName);
	return ;
}

void	Join::checkChannelFilling(t_data& myData) {
	if (myData.targetChannel->_channelLimit > 0 && myData.targetChannel->_channelClient.size() >= myData.targetChannel->_channelLimit) {
		myData.error = ERR_CHANNELISFULL(myData.client->_nickname, myData.targetChannel->_channelName);
	}
	return ;
}