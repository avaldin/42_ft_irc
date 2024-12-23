/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:51:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/23 20:45:04 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.class.hpp"
#include "Command.class.hpp"
#include "Error.define.hpp"
#include "Reply.define.hpp"
#include "Send.namespace.hpp"
#include "Invite.class.hpp"

Server* Invite::_server = Server::instantiate();

std::string(Invite::*Invite::_method[5])(t_data&) = {
	&Invite::checkChannelExist, 
	&Invite::checkChannelClient,
	&Invite::checkChannelOperator,
	&Invite::checkTargetExist,
	&Invite::checkChannelTarget};

Invite::Invite( void ) : _cmdName("INVITE") {
	return ;
}

Invite::~Invite( void ) {
	return ;
}

void	Invite::execute(Client const & client) {
	t_data			myData;
	std::string		error;
	
	myData.client = &client;
	if (this->_targetChannels.empty() || this->_targetUsers.empty())
		error = ERR_NEEDMOREPARAMS(this->_cmdName);
	myData.channel = this->_server->_serverChannel[this->_targetChannels.front()];
	for (int idx = 0;idx < 5 && error.empty(); idx++)
		error = (this->*_method[idx])(myData);
	if (!error.empty()) {
		Send::ToClient(client._clientID, error);
		return ;
	}
	myData.channel->addInvited(myData.targetID, myData.targetClient);
	Send::ToClient(client._clientID, RPL_INVITING(myData.channel->_channelName, myData.targetClient->_nickname));
	std::string const	reply = ":" + client._prefix + " " + "INVITE " + myData.targetClient->_nickname + " :" + myData.channel->_channelName;  
	Send::ToClient(myData.targetID, reply);
	return ;
}

std::string	Invite::checkChannelExist(t_data& myData) {
	myData.nameTargetChannel = this->_targetChannels.front(); //????
	myData.channel = this->_server->_serverChannel[myData.nameTargetChannel];

	if (!myData.channel)
		return ERR_NOSUCHCHANNEL(myData.nameTargetChannel);
	return "";
}

std::string	Invite::checkChannelClient(t_data& myData) {
	if(!myData.channel->isClient(myData.client->_clientID))
		return ERR_NOTONCHANNEL(myData.channel->_channelName);
	return "";
}

std::string	Invite::checkChannelOperator(t_data& myData) {
	if (!myData.channel->isOperator(myData.client->_clientID))
		return ERR_CHANOPRIVSNEEDED(myData.channel->_channelName);
	return "";
}

std::string	Invite::checkTargetExist(t_data& myData) {
	myData.targetUser = this->_targetUsers.front(); // PAS NICE
	myData.targetID = this->_server->_searchClientID[myData.targetUser->targetNickname];
	myData.targetClient = this->_server->_serverClient[myData.targetID];

	if (!myData.targetClient) 
		return ERR_NOSUCHNICK(myData.targetUser->targetNickname);
	return "";
}

std::string	Invite::checkChannelTarget(t_data& myData) {
	if (!myData.channel->isClient(myData.targetID)) 
		return ERR_USERONCHANNEL(myData.targetClient->_username, myData.channel->_channelName);
	return "";
}
