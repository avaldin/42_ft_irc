/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:01:51 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/18 20:22:20 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.class.hpp"
#include "Client.class.hpp"
#include "Server.class.hpp"
#include "Send.namespace.hpp"
#include "Reply.define.hpp"
#include "Error.define.hpp"
#include "Channel.class.hpp"

Server*	Topic::_server = Server::instantiate();

Topic::Topic( void ) {
	return ;
}

Topic::~Topic( void ) {
	return ;
}

void	Topic::execute(Client const & client) {
	if (this->_targetChannel.empty()) {
		Send::ToClient(client._clientID, ERR_NEEDMOREPARAMS(this->_cmdName));
		return ;
	}
	Channel const * currentChannel = this->_server->_serverChannel[this->_targetChannel];
	if (!currentChannel) {
		Send::ToClient(client._clientID, ERR_NOSUCHCHANNEL(this->_targetChannel));
		return ;
	}
	if (!currentChannel->isClient(client._clientID))
	if (this->_message.empty()) {
		if (currentChannel->_channelTopic.empty())
			Send::ToClient(client._clientID, RPL_NOTOPIC(currentChannel->_channelName));
		else
			Send::ToClient(client._clientID, RPL_TOPIC(currentChannel->_channelName, currentChannel->_channelTopic));
		return ;
	}
	
	return ;
}

