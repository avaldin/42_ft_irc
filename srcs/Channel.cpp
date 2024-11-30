/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:02:50 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/30 20:51:51 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.class.hpp"
#include "Client.class.hpp"

#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

Channel::Channel( void ) : _channelID(0), _channelName("") {
	return ;
}

Channel::~Channel( void ) {
	return ;
}

Channel::Channel(int channelID, std::string channelName) : _channelID(channelID), _channelName(channelName) {
	return ;
}
Channel::Channel(Channel const & src) : _channelID(src._channelID), _channelName(src._channelName) {
	*this = src;
	return ;
}

Channel& Channel::operator=(Channel const & rhs) {
	(void)rhs;
	return *this;
}

Channel*	Channel::instantiate(int channelID, std::string channelName) {
	return (new Channel(channelID, channelName));
}

void	Channel::sendToChannel(int const clientID, std::string const message) {
	for (std::map<int, Client*>::iterator it = this->_channelClient.begin(); it != this->_channelClient.end(); it++) {
		if (it->first != clientID) {
			int otherClient = it->second->getClientID();
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
