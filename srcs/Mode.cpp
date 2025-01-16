/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:10:51 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/16 21:02:17 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.class.hpp"
#include "Exception.class.hpp"
#include "Client.class.hpp"
#include "Channel.class.hpp"
#include "Error.define.hpp"
#include "Command.class.hpp"
#include "Send.namespace.hpp"

#include "Mode.class.hpp"
#include <cstdlib>
#include <cmath>

Server* Mode::_server = Server::instantiate();

void(Mode::*Mode::_funcMode[NUM_MODE])(t_mode const *, Channel * const, int const) = {
	&Mode::iFlag,
	&Mode::kFlag,
	&Mode::lFlag,
	&Mode::oFlag,
	&Mode::tFlag
};

void(Mode::*Mode::_method[CHECK_MODE])(t_data&) = {
	&Mode::checkRegistered,
	&Mode::checkParams,
	&Mode::checkChannelExist,
	
};

void	Mode::execute(Client& client) {
	t_data	myData;

	myData.client = &client;
	for (int idx = 0; idx < 3; idx++)
		(this->*_method[idx])(myData);
	int const	size = this->_mode.size();
	for (int idx = 0; idx < size; idx++) {
		t_mode*	currentMode = this->_mode[idx];
		int const modeNum = round(((static_cast<int>(currentMode->mode)-(float)105)*4)/11);
		if (modeNum < 5)
			(this->*_funcMode[modeNum])(currentMode, myData.channel, client._clientID);
		else {
			Send::ToClient(client._clientID, ERR_UNKNOWNMODE(static_cast<std::string>(&currentMode->mode)));
		}
	}
	return ;
}

void	Mode::tFlag(t_mode const * currentMode, Channel * const currentChannel, int const clientID) {
	if (!currentChannel->isOperator(clientID)) {
		Send::ToClient(clientID, ERR_CHANOPRIVSNEEDED(currentChannel->_channelName));
		return ;
	}
	currentChannel->_topicMode = currentMode->sign % 5 % 2;
	std::string const	reply = "MODE " + currentChannel->_channelName + static_cast<char>(currentMode->sign) + "t";
	Send::ToChannel(*currentChannel, reply);
	return ;
}

void	Mode::iFlag(t_mode const * currentMode, Channel * const currentChannel, int const clientID) {
	if (!currentChannel->isOperator(clientID)) {
		Send::ToClient(clientID, ERR_CHANOPRIVSNEEDED(currentChannel->_channelName));
		return ;
	}
	currentChannel->_inviteOnlyMode = currentMode->sign % 5 % 2;
	std::string const	reply = "MODE " + currentChannel->_channelName + static_cast<char>(currentMode->sign) + "i";
	Send::ToChannel(*currentChannel, reply);
	return ;
}

void	Mode::lFlag(t_mode const * currentMode, Channel * const currentChannel, int const clientID) {
	if (!currentChannel->isOperator(clientID)) {
		Send::ToClient(clientID, ERR_CHANOPRIVSNEEDED(currentChannel->_channelName));
		return ;
	}
	std::string reply = "MODE " + currentChannel->_channelName + static_cast<char>(currentMode->sign) + "l";
	if (currentMode->sign == '+') {
		currentChannel->_channelLimit = std::atoi(currentMode->args.c_str());
		reply += (" " + currentMode->args);
	}
	else if (currentMode->sign == '-')
		currentChannel->_channelLimit = -1;
	Send::ToChannel(*currentChannel, reply);
	return ;
}

void	Mode::kFlag(t_mode const * currentMode, Channel * const currentChannel, int const clientID) {
	if (!currentChannel->isOperator(clientID)) {
		Send::ToClient(clientID, ERR_CHANOPRIVSNEEDED(currentChannel->_channelName));
		return ;
	}
	if (currentMode->sign == '+')
		currentChannel->_channelPassword = currentMode->args;
	else if (currentMode->sign == '-')
		currentChannel->_channelPassword = "";
	std::string const	reply = "MODE " + currentChannel->_channelName + static_cast<char>(currentMode->sign) + "k";
	Send::ToChannel(*currentChannel, reply);
	return ;
}

void	Mode::oFlag(t_mode const * currentMode, Channel * const currentChannel, int const clientID) {
	if (!currentChannel->isOperator(clientID)) {
		Send::ToClient(clientID, ERR_CHANOPRIVSNEEDED(currentChannel->_channelName));
		return ;
	}
	int const	targetID = std::atoi(currentMode->args.c_str());
	if (!currentChannel->isClient(targetID)) {
		Send::ToClient(clientID, ERR_USERNOTINCHANNEL(currentMode->args, currentChannel->_channelName));
		return ;
	}
	if (currentMode->sign == '+')
		currentChannel->addOperator(targetID);
	else if (currentMode->sign == '-') {
		if (currentChannel->isOperator(targetID))
			currentChannel->deleteOperator(targetID);
		else
			return ;
	}
	std::string const	reply = "MODE " + currentChannel->_channelName + static_cast<char>(currentMode->sign) + "o " + currentMode->args;
	Send::ToChannel(*currentChannel, reply);
	return ; 
}

void	Mode::checkRegistered(t_data& myData) {
	if (myData.client->status != REGISTERED)
		myData.error = ERR_NOTREGISTRATED;
}

void	Mode::checkParams(t_data& myData) {
	if (this->_targetChannel.empty() || this->_mode.empty())
		myData.error = ERR_NEEDMOREPARAMS(this->_cmdName);
}

void	Mode::checkChannelExist(t_data& myData) {
	std::map<std::string, Channel*>::iterator	it = this->_server->_serverChannel.find(this->_targetChannel);
	
	if (it == this->_server->_serverChannel.end())
		myData.error = ERR_NOSUCHCHANNEL(this->_targetChannel);
	myData.channel = it->second;
}
