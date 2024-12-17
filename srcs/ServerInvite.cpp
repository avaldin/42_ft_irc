/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInvite.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:51:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/17 20:44:32 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.class.hpp"
#include "Command.class.hpp"
#include "Error.define.hpp"
#include "Reply.define.hpp"
#include "Send.namespace.hpp"

std::string(Server::Invite::*Server::Invite::_method[5])(void const *, int const &) = {&Server::Invite::checkChannelExist, 
																						&Server::Invite::checkChannelClient,
																						&Server::Invite::checkChannelOperator,
																						&Server::Invite::checkTargetExist,
																						&Server::Invite::checkChannelTarget};

void	Server::Invite::INVITE(Command* command, Client const & client) {
	t_user const *		targetUser = command->getTargetUsers().front();
	int const			targetID = this->_server->_searchClientID[targetUser->targetNickname];
	Client const *		targetClient = this->_server->_serverClient[targetID];
	std::string const	nameTargetChannel = command->getTargetChannels().front();
	Channel*			currentChannel = this->_server->_serverChannel[nameTargetChannel];
	std::string			error;
	
	while (error.empty()) {
		
	} 
	if (command->getTargetChannels().empty() || command->getTargetUsers().empty())
		error = ERR_NEEDMOREPARAMS(command->getCommand());
	
	else if (!currentChannel)
		error = ERR_NOSUCHCHANNEL(nameTargetChannel);
	else if (!currentChannel->isClient(client._clientID))
		error = ERR_NOTONCHANNEL(currentChannel->_channelName);
	else if (!currentChannel->isOperator(client._clientID))
		error = ERR_CHANOPRIVSNEEDED(currentChannel->_channelName);
	else if (!targetClient) 
		error = ERR_NOSUCHNICK(targetUser->targetNickname);
	else if (!currentChannel->isClient(targetID)) 
		error = ERR_USERONCHANNEL(targetClient->_username, currentChannel->_channelName);
	if (!error.empty()) {
		Send::ToClient(client._clientID, error);
		return ;
	}
	currentChannel->addInvited(targetID, targetClient);
	Send::ToClient(client._clientID, RPL_INVITING(currentChannel->_channelName, targetClient->_nickname));
	std::string const	reply = ":" + client._prefix + " " + "INVITE " + targetClient->_nickname + " :" + currentChannel->_channelName;  
	Send::ToClient(targetID, reply);
	return ;
}

std::string	Server::Invite::checkChannelExist(void const * currentChannel, int const & id) {
	(void)id;
	if (!currentChannel)
		return ;
}

std::string	Server::Invite::checkChannelClient(void const * currentChannel, int const & id) {
		
}

std::string	Server::Invite::checkChannelOperator(void const * currentChannel, int const & id) {
		
}

std::string	Server::Invite::checkTargetExist(void const * currentChannel, int const & id) {
		
}

std::string	Server::Invite::checkChannelTarget(void const * currentChannel, int const & id) {
		
}
