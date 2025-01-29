/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:10:51 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/22 13:52:27 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.class.hpp"
#include "Client.class.hpp"
#include "Channel.class.hpp"
#include "Error.define.hpp"
#include "Reply.define.hpp"
#include "Parser.class.hpp"
#include "Send.namespace.hpp"

#include "Mode.class.hpp"
#include <sstream>

Server* Mode::_server = Server::instantiate();

Mode::~Mode(void)
{
	for (std::vector<t_mode*>::iterator it = this->_mode.begin(); it != this->_mode.end(); it++)
		delete (*it);
}

void(Mode::*Mode::_funcMode[NUM_MODE])(t_mode const *, t_data& myData) = {
	&Mode::iFlag,
	&Mode::kFlag,
	&Mode::lFlag,
	&Mode::oFlag,
	&Mode::tFlag,
	&Mode::unknownFlag,
};

void(Mode::*Mode::_method[CHECK_MODE])(t_data&) = {
	&Mode::checkRegistered,
	&Mode::checkParams,
	&Mode::checkChannelExist,
	&Mode::checkChannelOperator,
	&Mode::checkClientTarget,
};

void	Mode::execute(Client& client) {
	t_data	myData;

	myData.client = &client;
	for (myData.idxCheck = 0; myData.idxCheck < 4 && myData.error.empty(); myData.idxCheck++)
		(this->*_method[myData.idxCheck])(myData);
	if (!myData.error.empty()) {
		Send::ToClient(client._clientID, myData.error);
		return ;
	}
	if (this->_mode.empty())
	{
		Send::ToClient(client._clientID, RPL_CHANNELMODEIS(myData.client->_nickname, myData.channel->_channelName, modeString(*myData.channel)));
		return ;
	}
	int const	size = this->_mode.size();
	for (int idx = 0; idx < size; idx++) {
		myData.mode = this->_mode[idx];
		(this->*_funcMode[idxFuncMode(myData.mode->mode)])(myData.mode, myData);
		if (myData.error.empty()) {
			std::string const	reply = "MODE " + myData.channel->_channelName + static_cast<char>(myData.mode->sign) + myData.mode->mode + " " + myData.mode->args;
			Send::ToChannel(*myData.channel, reply);
		}
		else
			Send::ToClient(client._clientID, myData.error);
	}
	return ;
}

void	Mode::tFlag(t_mode const * currentMode, t_data& myData) {
	myData.channel->_topicMode = currentMode->sign % 5 % 2;
	return ;
}

void	Mode::iFlag(t_mode const * currentMode, t_data& myData) {
	myData.channel->_inviteOnlyMode = currentMode->sign % 5 % 2;
	return ;
}

void	Mode::lFlag(t_mode const * currentMode, t_data& myData) {
	if (currentMode->sign == '+') {
		if (!currentMode->args.empty()) {
			std::stringstream	limitSS;
			limitSS << currentMode->args;
			limitSS >> myData.channel->_channelLimit;
		}
		else
			myData.error = ERR_NEEDMOREPARAMS(myData.client->_nickname, this->cmdName);
	}
	else if (currentMode->sign == '-')
		myData.channel->_channelLimit = -1;
	return ;
}

void	Mode::kFlag(t_mode const * currentMode, t_data& myData) {
	if (currentMode->sign == '+') {
		if (!currentMode->args.empty())
			myData.channel->_channelPassword = currentMode->args;
		else
			myData.error = ERR_NEEDMOREPARAMS(myData.client->_nickname, this->cmdName);
	}
	else if (currentMode->sign == '-')
		myData.channel->_channelPassword = "";
	return ;
}

void	Mode::oFlag(t_mode const * currentMode, t_data& myData) {
	myData.target = this->_server->findClientNickname(currentMode->args);
	
	(this->*_method[myData.idxCheck])(myData);
	if (!myData.error.empty())
		return ;
	if (currentMode->sign == '+')
		myData.channel->addOperator(myData.target->_clientID);
	else if (currentMode->sign == '-') {
		if (myData.channel->isOperator(myData.target->_clientID))
			myData.channel->deleteOperator(myData.target->_clientID);
		else
			return ;
	}
	return ; 
}

void	Mode::unknownFlag(t_mode const * currentMode, t_data& myData) {
	myData.error = ERR_UNKNOWNMODE(myData.client->_nickname, currentMode->mode);
	return ;
}

unsigned int	Mode::idxFuncMode(unsigned int const mode) {
	static unsigned int const	tab[5] = {0,2,3,6,11};
	int							idx;
	
	for (idx = 0;idx < 5;idx++) {
		if (tab[idx] == (mode - LOWEST_MODE))
			break ;
	}
	return idx;
}

void	Mode::checkRegistered(t_data& myData) {
	if (myData.client->status != REGISTERED)
		myData.error = ERR_NOTREGISTRATED(myData.client->_nickname);
	return ;
}

void	Mode::checkParams(t_data& myData) {
	if (this->_targetChannel.empty())
		myData.error = ERR_NEEDMOREPARAMS(myData.client->_nickname, this->cmdName);
}

void	Mode::checkChannelExist(t_data& myData) {
	std::map<std::string, Channel*>::iterator	it = this->_server->_serverChannel.find(this->_targetChannel);
	
	if (it == this->_server->_serverChannel.end())
		myData.error = ERR_NOSUCHCHANNEL(myData.client->_nickname, this->_targetChannel);
	else
		myData.channel = it->second;
	return ;
}

void	Mode::checkChannelOperator(t_data& myData) {
	if (!myData.channel->isOperator(myData.client->_clientID))
		myData.error = ERR_CHANOPRIVSNEEDED(myData.client->_nickname, myData.channel->_channelName);
	return ;
}

void	Mode::checkClientTarget(t_data& myData) {
	if (!myData.channel->isClient(myData.target->_clientID)) 
		myData.error = ERR_USERNOTINCHANNEL(myData.client->_nickname, myData.mode->args, myData.channel->_channelName);
	return ;
}

std::string	Mode::modeString(Channel& channel) {
	std::string			mode;
	std::stringstream	ss;

	if (channel._channelLimit != (unsigned int)-1)
	{
		ss << channel._channelLimit;
		mode += "l";
	}
	if (!channel._channelPassword.empty()) {
		mode += "k";
		if (!ss.str().empty())
			ss << " ";
		ss << channel._channelPassword;
	}
	if (channel._topicMode)
		mode += "t";
	if (channel._inviteOnlyMode)
		mode += "i";
	if (!ss.str().empty()) {
		mode += " " + ss.str();
	}
	return (mode);
}


