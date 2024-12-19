/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:01:51 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/19 18:22:37 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.class.hpp"
#include "Client.class.hpp"
#include "Server.class.hpp"
#include "Send.namespace.hpp"
#include "Reply.define.hpp"
#include "Error.define.hpp"
#include "Channel.class.hpp"

#include <cstring>

Server*	Topic::_server = Server::instantiate();

std::string(Topic::*Topic::_method[4])(t_data const &) const = {
	&Topic::checkChannelClient,
	&Topic::checkCommandMessage,
	&Topic::checkChannelClient,
	&Topic::checkChannelOperator};

Topic::Topic( void ) : _cmdName("TOPIC") {
	return ;
}

Topic::~Topic( void ) {
	return ;
}

void	Topic::execute(Client const & client) {
	t_data		myData;
	std::string	error;

	myData.client = &client;
	if (this->_targetChannel.empty())
		error = ERR_NEEDMOREPARAMS(this->_cmdName);	
	myData.channel = this->_server->_serverChannel[this->_targetChannel];
	for (int idx = 0;idx < 4 && error.empty(); idx++) {
		std::string(Topic::*func)(t_data const &)const = this->_method[idx];
		error = (this->*func)(myData);
	}
	if (!error.empty()) {
		Send::ToClient(client._clientID, error);
		return ;
	}
	myData.channel->_channelTopic = this->_topic;
	Send::ToChannel(*myData.channel, client._prefix + " TOPIC " + myData.channel->_channelName + " :" + myData.channel->_channelTopic);
	return ;
}

std::string	Topic::checkChannelExist(t_data const & myData) const {
	if (!myData.channel)
		return ERR_NOSUCHCHANNEL(this->_targetChannel);
	return "";
}

std::string	Topic::checkCommandMessage(t_data const & myData) const {
	if (this->_topic.empty() && myData.channel->_channelTopic.empty())
		return RPL_NOTOPIC(myData.channel->_channelName);
	else if (this->_topic.empty())
		return RPL_TOPIC(myData.channel->_channelName, myData.channel->_channelTopic);
	return "";
}

std::string	Topic::checkChannelClient(t_data const & myData) const {
	if (!myData.channel->isClient(myData.client->_clientID))
		return ERR_NOTONCHANNEL(myData.channel->_channelName);
	return "";
}

std::string	Topic::checkChannelOperator(t_data const & myData) const {
	if (!myData.channel->isOperator(myData.client->_clientID))
		return ERR_CHANOPRIVSNEEDED(myData.channel->_channelName);
	return "";
}
