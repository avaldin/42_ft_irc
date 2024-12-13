/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInvite.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 17:51:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/13 20:10:33 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.class.hpp"
#include "Command.class.hpp"
#include "Error.define.hpp"
#include "Reply.define.hpp"

void	Server::INVITE(Command* command, int const clientID) {
	if (command->getTargetChannels().empty()) {
		this->sendToClient(this->_mySocket, clientID, ERR_NEEDMOREPARAMS(command->getCommand()));
		return ;
	}
	std::string const	nameTargetChannel = command->getTargetChannels().front();
	Channel *	const	currentChannel = this->_serverChannel[nameTargetChannel];
	
	if (!currentChannel->isClient(clientID)) {
		this->sendToClient(this->_mySocket, clientID, ERR_NOTONCHANNEL(currentChannel->_channelName));
		return ;
	}
	if (!currentChannel->isOperator(clientID)) {
		this->sendToClient(this->_mySocket, clientID, ERR_CHANOPRIVSNEEDED(currentChannel->_channelName));
		return ;
	}
	if (!currentChannel) {
		this->sendToClient(this->_mySocket, clientID, ERR_NOSUCHCHANNEL(nameTargetChannel));
		return ;
	}
	t_user const *	targetUser = command->getTargetUsers().front();
	int const		targetID = this->_searchClientID[targetUser->targetNickname];
	Client*			targetClient = this->_serverClient[targetID];
	
	if (!targetClient) {
		this->sendToClient(this->_mySocket, clientID, ERR_NOSUCHNICK(targetClient->_nickname));
		return ;
	}
	if (!currentChannel->isClient(targetID)) {
		this->sendToClient(this->_mySocket, clientID, ERR_USERONCHANNEL(targetClient->_username, currentChannel->_channelName));
		return ;
	}
	currentChannel->addInvited(targetID, targetClient);
	this->sendToClient(this->_mySocket, clientID, RPL_INVITING(currentChannel->_channelName, targetClient->_nickname));
	this->sendToClient(this->_mySocket, clientID, ""); // Change something on send command that s not work easily
	return ;
}
