/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:01:51 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/13 18:59:27 by tmouche          ###   ########.fr       */
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

#include <iostream>

Server*	Topic::_server = Server::instantiate();

void(Topic::*Topic::_method[CHECK_TOPIC])(t_data&) = {
	&Topic::checkRegistered,
	&Topic::checkParams,
	&Topic::checkChannelExist,
	&Topic::checkCommandMessage,
	&Topic::checkChannelClient,
	&Topic::checkChannelOperator};

Topic::Topic( void ) : _cmdName("TOPIC") {
	return ;
}

Topic::~Topic( void ) {
	return ;
}

void	Topic::execute(Client& client) {
	t_data	myData;

	myData.client = &client;
	for (int idx = 0;idx < CHECK_TOPIC && myData.error.empty(); idx++)
		(this->*_method[idx])(myData);
	if (!myData.error.empty()) {
		Send::ToClient(client._clientID, myData.error);
		return ;
	}
	myData.channel->_channelTopic = this->_topic;
	Send::ToChannel(*myData.channel, client._prefix + " TOPIC " + myData.channel->_channelName + " :" + myData.channel->_channelTopic);
	return ;
}

void	Topic::checkRegistered(t_data& myData) {
	if (myData.client->status != REGISTERED)
		myData.error = ERR_NOTREGISTRATED;
	return ;
}

void	Topic::checkParams(t_data& myData) {
	if (this->_targetChannel.empty())
		myData.error = ERR_NEEDMOREPARAMS(this->_cmdName);
	return ;
}

void	Topic::checkChannelExist(t_data& myData) {
	std::map<std::string, Channel*>::iterator it = this->_server->_serverChannel.find(this->_targetChannel);

	if (it == this->_server->_serverChannel.end())
		myData.error = ERR_NOSUCHCHANNEL(this->_targetChannel);
	myData.channel = it->second;
	return ;
}

void	Topic::checkCommandMessage(t_data& myData) {
	if (this->_topic.empty() && myData.channel->_channelTopic.empty())
		myData.error = RPL_NOTOPIC(myData.channel->_channelName);
	else if (this->_topic.empty())
		myData.error = RPL_TOPIC(myData.channel->_channelName, myData.channel->_channelTopic);
	return ;
}

void	Topic::checkChannelClient(t_data& myData) {
	if (!myData.channel->isClient(myData.client->_clientID))
		myData.error =  ERR_NOTONCHANNEL(myData.channel->_channelName);
	return ;
}

void	Topic::checkChannelOperator(t_data& myData) {
	if (!myData.channel->isOperator(myData.client->_clientID))
		myData.error = ERR_CHANOPRIVSNEEDED(myData.channel->_channelName);
	return ;
}
