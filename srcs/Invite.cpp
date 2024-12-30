/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:51:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/30 17:53:55 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.class.hpp"
#include "Command.class.hpp"
#include "Error.define.hpp"
#include "Reply.define.hpp"
#include "Send.namespace.hpp"
#include "Invite.class.hpp"

Server* Invite::_server = Server::instantiate();

void(Invite::*Invite::_method[7])(t_data&) = {
	&Invite::checkRegistered,
	&Invite::checkParams,
	&Invite::checkChannelExist, 
	&Invite::checkChannelClient,
	&Invite::checkChannelOperator,
	&Invite::checkTargetExist,
	&Invite::checkChannelTarget};

void	Invite::execute(Client const & client) {
	t_data	myData;
	
	myData.client = &client;
	for (int idx = 0;idx < 7 && myData.error.empty(); idx++)
		(this->*_method[idx])(myData);
	if (!myData.error.empty()) {
		Send::ToClient(client._clientID, myData.error);
		return ;
	}
	myData.channel->addInvited(myData.client->_clientID, myData.targetClient);
	Send::ToClient(client._clientID, RPL_INVITING(myData.channel->_channelName, myData.targetClient->_nickname));
	std::string const	reply = ":" + client._prefix + " " + "INVITE " + myData.targetClient->_nickname + " :" + myData.channel->_channelName;  
	Send::ToClient(myData.client->_clientID, reply);
	return ;
}

void	Invite::checkRegistered(t_data& myData) {
	if (myData.client->status != REGISTERED)
		myData.error = ERR_NOTREGISTRATED;
}

void	Invite::checkParams(t_data& myData) {
	if (this->_targetChannels.empty() || this->_targetUsers.empty())
		myData.error = ERR_NEEDMOREPARAMS(this->_cmdName);
}

void	Invite::checkChannelExist(t_data& myData) {
	myData.nameTargetChannel = this->_targetChannels.front();
	myData.channel = this->_server->_serverChannel[myData.nameTargetChannel];

	if (!myData.channel)
		myData.error = ERR_NOSUCHCHANNEL(myData.nameTargetChannel);
}

void	Invite::checkChannelClient(t_data& myData) {
	if(!myData.channel->isClient(myData.client->_clientID))
		myData.error = ERR_NOTONCHANNEL(myData.channel->_channelName);
}

void	Invite::checkChannelOperator(t_data& myData) {
	if (!myData.channel->isOperator(myData.client->_clientID))
		myData.error = ERR_CHANOPRIVSNEEDED(myData.channel->_channelName);
}

void	Invite::checkTargetExist(t_data& myData) {
	myData.targetUser = this->_targetUsers.front();
	myData.targetClient = this->_server->_serverNickname[myData.targetUser->targetNickname];

	if (!myData.targetClient) 
		myData.error = ERR_NOSUCHNICK(myData.targetUser->targetNickname);
}

void	Invite::checkChannelTarget(t_data& myData) {
	if (!myData.channel->isClient(myData.targetClient->_clientID)) 
		myData.error =  ERR_USERONCHANNEL(myData.targetClient->_username, myData.channel->_channelName);
}
