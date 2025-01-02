/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:01:25 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/02 18:05:01 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Join.class.hpp"

#include "Error.define.hpp"
#include "Reply.define.hpp"

#include "Send.namespace.hpp"

#include "Server.class.hpp"
#include "Client.class.hpp"
#include "Channel.class.hpp"

Server*	Join::_server = Server::instantiate();

void(Join::*Join::_method[NB_CHECK])(t_data&) = {
	
};

void	Join::execute(Client& client) {
	t_data	myData;
	
	myData.client = &client;
	for (int idx = 0; idx < NB_CHECK && myData.error.empty(); idx++)
		(this->*_method[idx])(myData);
	int const sizeChannels = this->_targetChannels.size();
	int const sizeKey = this->_targetKeys.size();
	for (int idx, idxKey = 0; idx < sizeChannels; idx++, idxKey++) {
		std::string&	targetName = this->_targetChannels[idx];
		Channel*		target = this->_server->_serverChannel[targetName];

		if (!target) {
			if (targetName[0] == '&')
				target = Channel::instantiateChannel(MODE, targetName);
			else
				return ; // DO SOMETHING
			target->addClient(client._clientID, &client);
			target->addOperator(client._clientID);
			target->_channelPassword.clear(); 
			if (idxKey < sizeKey)
				target->_channelPassword = this->_targetKeys[idxKey];
 		}
		else {
			if (idxKey < sizeKey && target->_channelPassword.compare(this->_targetKeys[idx]))
				myData.error = ERR_BADCHANNELKEY(target->_channelName);
			if (target->_inviteOnlyMode && !target->isInvited(myData.client->_clientID))
				myData.error = ERR_INVITEONLYCHAN(target->_channelName);
			if (target->_channelClient.size() == target->_channelLimit)
				myData.error = ERR_CHANNELISFULL(target->_channelName);
			target->addClient(myData.client->_clientID, myData.client);
		}
	}
	return ;
}

void	Join::checkRegistered(t_data& myData) {
	if (myData.client->status != REGISTERED)
		myData.error = ERR_NOTREGISTRATED;
	return ;
}

void	Join::checkParams(t_data& myData) {
	if (this->_targetChannels.empty())
		myData.error = ERR_NEEDMOREPARAMS(this->_cmdName);
	return ;
}
