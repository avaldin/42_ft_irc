/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:02:50 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/29 20:14:41 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.class.hpp"
#include "Client.class.hpp"

Channel::Channel( void ) {
	return ;
}

Channel::~Channel( void ) {
	return ;
}

Channel::Channel(Channel const & src) {
	return ;
}

Channel& Channel::operator=(Channel const & rhs) {
	return ;
}

void	Channel::sendToChannel(int clientID, std::string token) {
	std::string nickname = this->_channelClient[clientID]->getnickname() + ": " + token;
	
	for (std::map<int, Client*>::iterator it = this->_channelClient.begin(); it != this->_channelClient.end(); it++) {
		if (it->first != clientID)
			int otherClient = it->second->getClientID();
			send
	}
	return ;
}