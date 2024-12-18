/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:51:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/18 19:32:00 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.class.hpp"
#include "Command.class.hpp"
#include "Error.define.hpp"
#include "Reply.define.hpp"
#include "Send.namespace.hpp"
#include "Invite.class.hpp"

Server* const Invite::_server = Server::instantiate();

std::string(Invite::*Invite::_method[5])(t_data&, Client const &) = {&Invite::checkChannelExist, 
	&Invite::checkChannelClient,
	&Invite::checkChannelOperator,
	&Invite::checkTargetExist,
	&Invite::checkChannelTarget};

Invite::Invite( void ) {
	return ;
}

Invite::~Invite( void ) {
	return ;
}

void	Invite::execute(Client const & client) {
	t_data			myData;
	std::string		error;
	
	if (this->_targetChannels.empty() || this->_targetUsers.empty())
		error = ERR_NEEDMOREPARAMS(this->_cmdName);
	for (int idx = 0;idx < 5 && error.empty(); idx++) {
		std::string(Invite::*func)(t_data&, Client const &) = this->_method[idx];
		error = (this->*func)(myData, client);
	} 
	if (!error.empty()) {
		Send::ToClient(client._clientID, error);
		return ;
	}
	myData.currentChannel->addInvited(myData.targetID, myData.targetClient);
	Send::ToClient(client._clientID, RPL_INVITING(myData.currentChannel->_channelName, myData.targetClient->_nickname));
	std::string const	reply = ":" + client._prefix + " " + "INVITE " + myData.targetClient->_nickname + " :" + myData.currentChannel->_channelName;  
	Send::ToClient(myData.targetID, reply);
	return ;
}

std::string	Invite::checkChannelExist(t_data& data, Client const & client) {
	data.nameTargetChannel = this->_targetChannels.front();
	data.currentChannel = this->_server->_serverChannel[data.nameTargetChannel];

	if (!data.currentChannel)
		return ERR_NOSUCHCHANNEL(data.nameTargetChannel);
	return "";
}

std::string	Invite::checkChannelClient(t_data& data, Client const & client) {
	if(!data.currentChannel->isClient(client._clientID))
		return ERR_NOTONCHANNEL(data.currentChannel->_channelName);
	return "";
}

std::string	Invite::checkChannelOperator(t_data& data, Client const & client) {
	if (!data.currentChannel->isOperator(client._clientID))
		return ERR_CHANOPRIVSNEEDED(data.currentChannel->_channelName);
	return "";
}

std::string	Invite::checkTargetExist(t_data& data, Client const & client) {
	data.targetUser = this->_targetUsers.front();
	data.targetID = this->_server->_searchClientID[data.targetUser->targetNickname];
	data.targetClient = this->_server->_serverClient[data.targetID];

	if (!data.targetClient) 
		return ERR_NOSUCHNICK(data.targetUser->targetNickname);
	return "";
}

std::string	Invite::checkChannelTarget(t_data& data, Client const & client) {
	if (!data.currentChannel->isClient(data.targetID)) 
		return ERR_USERONCHANNEL(data.targetClient->_username, data.currentChannel->_channelName);
	return "";
}
