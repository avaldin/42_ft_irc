/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:01:51 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/26 19:24:23 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Topic.class.hpp"
#include "Client.class.hpp"
#include "Server.class.hpp"
#include "Send.namespace.hpp"
#include "Reply.define.hpp"
#include "Error.define.hpp"
#include "Channel.class.hpp"
#include "Command.class.hpp"

#include <cstring>

Server*	Topic::_server = Server::instantiate();

std::string(Topic::*Topic::_method[6])(t_data&) = {
	&Topic::checkRegistered,
	&Topic::checkParams,
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
	for (int idx = 0;idx < 4 && error.empty(); idx++)
		error = (this->*_method[idx])(myData);
	if (!error.empty()) {
		Send::ToClient(client._clientID, error);
		return ;
	}
	myData.channel->_channelTopic = this->_topic;
	Send::ToChannel(*myData.channel, client._prefix + " TOPIC " + myData.channel->_channelName + " :" + myData.channel->_channelTopic);
	return ;
}

std::string Topic::checkRegistered(t_data& myData) {
	if (myData.client->status != REGISTERED)
		return ERR_NOTREGISTRATED;
	return "";
}

std::string	Topic::checkParams(t_data& myData) {
	if (this->_targetChannel.empty())
		return ERR_NEEDMOREPARAMS(this->_cmdName);
	return "";
}

std::string	Topic::checkChannelExist(t_data& myData) {
	myData.channel = this->_server->_serverChannel[this->_targetChannel];

	if (!myData.channel)
		return ERR_NOSUCHCHANNEL(this->_targetChannel);
	return "";
}

std::string	Topic::checkCommandMessage(t_data& myData) {
	if (this->_topic.empty() && myData.channel->_channelTopic.empty())
		return RPL_NOTOPIC(myData.channel->_channelName);
	else if (this->_topic.empty())
		return RPL_TOPIC(myData.channel->_channelName, myData.channel->_channelTopic);
	return "";
}

std::string	Topic::checkChannelClient(t_data& myData) {
	if (!myData.channel->isClient(myData.client->_clientID))
		return ERR_NOTONCHANNEL(myData.channel->_channelName);
	return "";
}

std::string	Topic::checkChannelOperator(t_data& myData) {
	if (!myData.channel->isOperator(myData.client->_clientID))
		return ERR_CHANOPRIVSNEEDED(myData.channel->_channelName);
	return "";
}
