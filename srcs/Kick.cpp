/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 00:42:16 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/21 02:22:47 by tmouche          ###   ########.fr       */
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

Kick::Kick( void ) : _cmdName("KICK") {
	return ;
}

Kick::~Kick( void ) {
	return ;
}

void	Kick::execute(Client const & client) {
	// t_data		myData;
	std::string	error;
	
	if (this->_targetChannels.empty() || this->_targetUsers.empty())
		error = ERR_NEEDMOREPARAMS(this->_cmdName);
	int const sizeChannel = this->_targetChannels.size();
	for (int idxChannel = 0; idxChannel < sizeChannel; idxChannel++) {
		Channel*	channel = this->_server->_serverChannel[this->_targetChannels[idxChannel]];
		if (!channel) {
			Send::ToClient(client._clientID, ERR_NOSUCHCHANNEL(this->_targetChannels[idxChannel]));
			continue ;
		}
		else if (!channel->isClient(client._clientID)) {
			Send::ToClient(client._clientID, ERR_NOTONCHANNEL(this->_targetChannels[idxChannel]));
			continue ;
		}
		else if (!channel->isOperator(client._clientID)) {
			Send::ToClient(client._clientID, ERR_CHANOPRIVSNEEDED(this->_targetChannels[idxChannel]));
			continue ;
		}
		int const sizeUser = this->_targetUsers.size();
		for (int idxClient = 0; idxClient < sizeUser; idxClient++) {
			t_user const *	targetUser = this->_targetUsers[idxClient];
			int const		targetID = this->_server->_searchClientID[targetUser->targetNickname];
			Client const *	targetClient = this->_server->_serverClient[targetID];
			if (!targetClient || !channel->isClient(targetID)) {
				Send::ToClient(client._clientID, ERR_USERNOTINCHANNEL(targetUser->targetNickname, channel->_channelName));
				continue ;
			}
			channel->deleteClient(targetID);
			Send::ToChannel(*channel, client._prefix + " KICK " + channel->_channelName + " " + this->_message);
			Send::ToClient(targetID, client._prefix + " KICK " + channel->_channelName + " " + this->_message);
		}
	} 
	return ;
}