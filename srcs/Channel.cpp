/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:02:50 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/27 16:49:29 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.class.hpp"
#include "Client.class.hpp"

#include <netinet/in.h>
#include <sys/socket.h>

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

void	Channel::sendToChannel(std::string const message) const {
	for (std::map<int, Client const *>::const_iterator it = this->_channelClient.begin(); it != this->_channelClient.end(); it++) {
		send(it->first, message.c_str(), message.size(), 0);
	}
	return ;
}

void Channel::privMsgToChannel(const std::string message, int clientID) const
{
	for (std::map<int, Client const *>::const_iterator it = this->_channelClient.begin(); it != this->_channelClient.end(); it++) {
		if (it->second->_clientID != clientID)
			send(it->second->_clientID, (message + "\r\n").c_str(), message.size() + 2, 0);
	}
}

void	Channel::addOperator(int const clientID) {
	this->_channelOperator[clientID] = this->_channelClient[clientID];
	return ;
}

void	Channel::deleteOperator(int const clientID) {
	this->_channelOperator.erase(clientID);
	return ;
}

void	Channel::addClient(int const clientID, Client const * client) {
	this->_channelClient[clientID] = client;
	return ;
}

void	Channel::deleteClient(int const clientID) {
	this->_channelClient.erase(clientID);
	return ;
}

void	Channel::addInvited(int const clientID, Client const * client) {
	this->_invitedClient[clientID] = client;
	return ;
}

void	Channel::deleteInvited(int const clientID) {
	this->_invitedClient.erase(clientID);
	return ;
}

bool	Channel::isOperator(int const clientID) {
	if (this->_channelOperator.find(clientID) == this->_channelOperator.end())
		return false;
	return true;
}

bool	Channel::isInvited(int const clientID) {
	if (this->_invitedClient.find(clientID) == this->_invitedClient.end())
		return false;
	return true;
}

bool	Channel::isClient(int const clientID) {
	if (this->_channelClient.find(clientID) == this->_channelClient.end())
		return false;
	return true;
}

bool	Channel::isClient(std::string const clientNick) {
	for (std::map<int, Client const *>::iterator it = this->_channelClient.begin(); it != this->_channelClient.end(); it++) {
			if (!it->second->_nickname.compare(clientNick))
				return true;
		}
		return false;
}
