/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:01:25 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/02 19:40:45 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.class.hpp"

#include "Error.define.hpp"
#include "Reply.define.hpp"

#include "Send.namespace.hpp"

#include "Server.class.hpp"
#include "Client.class.hpp"
#include "Channel.class.hpp"

Server*	Join::_server = Server::instantiate();

void(Join::*Join::_method[CHECK_JOIN])(t_data&) = {
	&Join::checkRegistered,
	&Join::checkParams,
	&Join::checkChannelName,
	&Join::checkChannelKey,
	&Join::checkChannelInvite,
	&Join::checkChannelFilling};

void	Join::execute(Client& client) {
	t_data	myData;
	int		idx;

	myData.client = &client;
	for (idx = 0; idx < 2 && myData.error.empty(); idx++)
		(this->*_method[idx])(myData);
	int const sizeChannels = this->_targetChannels.size();
	int const sizeKey = this->_targetKeys.size();
	for (int idxChannel = 0, idxKey = 0; idxChannel < sizeChannels && myData.error.empty(); idxChannel++, idxKey++) {
		myData.targetName = this->_targetChannels[idxChannel];
		(this->*_method[idx])(myData);
		myData.targetChannel = this->_server->_serverChannel[myData.targetName];
		if (myData.targetChannel) {
			if (idxKey < sizeKey)
				myData.targetKey = this->_targetKeys[idxKey];
			for (idx = 2;idx < CHECK_JOIN && myData.error.empty(); idx++) {
				(this->*_method[idx])(myData);
 			}
			myData.targetChannel->addClient(client._clientID, &client);
		}
		else {
			myData.targetChannel = Channel::instantiateChannel(MODE, myData.targetName);
			myData.targetChannel->addClient(client._clientID, &client);
			myData.targetChannel->addOperator(client._clientID);
			myData.targetChannel->_channelPassword.clear();
		}
		if (!myData.error.empty())
			Send::ToClient(client._clientID, myData.error);
		myData.error.clear();
		myData.targetKey.clear();
		myData.targetChannel = NULL;
	}
	return ;
}

void	Join::checkRegistered(t_data& myData) {
	if (myData.client->status != REGISTERED)
		myData.error = ERR_NOTREGISTRATED;
	return ;
}

void	Join::checkParams(t_data& myData) {
	if (this->_targetChannels.empty())
		myData.error = ERR_NEEDMOREPARAMS(this->_cmdName);
	return ;
}

void	Join::checkChannelName(t_data& myData) {
	int const size = myData.targetName.size();
	
	if (size > 50 || myData.targetName[0] != '&')
		myData.error = ERR_BADCHANMASK(myData.targetName);	
	for (int idx = 0; idx < size && myData.error.empty(); idx++) {
		char const	c = myData.targetName[idx]; 
		if (c <= 32 || c == ',' || c == ':')
			myData.error = ERR_BADCHANMASK(myData.targetName);
	}
	return ;
}

void	Join::checkChannelKey(t_data& myData) {
	if (!myData.targetKey.empty() && myData.targetKey.compare(myData.targetChannel->_channelPassword))
		myData.error = ERR_BADCHANNELKEY(myData.targetChannel->_channelName);
	return ;
}

void	Join::checkChannelInvite(t_data& myData) {
	if (!myData.targetChannel->_inviteOnlyMode && !myData.targetChannel->isInvited(myData.client->_clientID))
		myData.error = ERR_INVITEONLYCHAN(myData.targetChannel->_channelName);
	return ;
}

void	Join::checkChannelFilling(t_data& myData) {
	if (myData.targetChannel->_channelLimit > 0 && myData.targetChannel->_channelClient.size() == myData.targetChannel->_channelLimit)
		myData.error = ERR_CHANNELISFULL(myData.targetChannel->_channelName);
	return ;
}