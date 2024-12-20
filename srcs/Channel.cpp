/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:02:50 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/02 17:03:48 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.class.hpp"
#include "Client.class.hpp"

#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

Channel::Channel( void ) : _channelType(MODE), _channelName("") {
	return ;
}

Channel::~Channel( void ) {
	return ;
}

Channel::Channel(t_channelType channelType, std::string channelName) : _channelType(channelType), _channelName(channelName) {
	this->_channelLimit = 0;
	this->_channelPassword = "";
	this->_channelTopic = "";
	this->_topicMode = true;
	this->_inviteOnlyMode = false;
	return ;
}
Channel::Channel(Channel const & src) : _channelType(src._channelType), _channelName(src._channelName) {
	*this = src;
	return ;
}

Channel& Channel::operator=(Channel const & rhs) {
	if (this != &rhs) {
		this->_channelLimit =rhs._channelLimit;
		this->_channelPassword = rhs._channelPassword;
		this->_channelTopic = rhs._channelTopic;
		this->_topicMode = rhs._topicMode;
		this->_inviteOnlyMode = rhs._inviteOnlyMode;
		this->_channelClient = rhs._channelClient;
		this->_channelOperator = rhs._channelOperator;
		this->_channelCreator = rhs._channelCreator;
	}
	return *this;
}

Channel*	Channel::instantiateChannel(t_channelType channelType, std::string channelName) {
	return (new Channel(channelType, channelName));
}

void	Channel::uninstantiateChannel(Channel* oldChannel) {
	if (oldChannel)
		delete oldChannel;
	return ;
}

void	Channel::sendToChannel(int const clientID, std::string const message) {
	for (std::map<int, Client*>::iterator it = this->_channelClient.begin(); it != this->_channelClient.end(); it++) {
		if (it->first != clientID) {
			int otherClient = it->second->_clientID;
			send(otherClient, message.c_str(), message.size(), 0);
		}
	}
	return ;
}

bool	Channel::isOperator(int const clientID) {
	if (this->_channelOperator[clientID])
		return true;
	return false;
}
