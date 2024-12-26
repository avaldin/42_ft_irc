/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:10:51 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/19 18:44:42 by tmouche          ###   ########.fr       */
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

Server* Mode::_server = Server::instantiate();

Mode::Mode( void ) : _cmdName("MODE") {
	return ;
}

Mode::~Mode( void ) {
	return ;
}

void	Mode::execute(Client const & client) {
	if (this->_targetChannels.empty() || this->_mode.empty()) {
		Send::ToClient(client._clientID, ERR_NEEDMOREPARAMS(this->_cmdName));
		return ;	
	}
	Channel * const	currentChannel = this->_server->_serverChannel[this->_targetChannels.front()];
	if (!currentChannel) {
		Send::ToClient(client._clientID, ERR_NOSUCHCHANNEL(currentChannel->_channelName));
		return ;
	}
	std::map<char,void(Mode::*)(t_mode const *, Channel * const , int const)> _modeCmd;
	_modeCmd['t'] = &Mode::tFlag;
	_modeCmd['i'] = &Mode::iFlag;
	_modeCmd['l'] = &Mode::lFlag;
	_modeCmd['k'] = &Mode::kFlag;
	_modeCmd['o'] = &Mode::oFlag;
	int const	size = this->_mode.size();
	for (int idx = 0; idx < size; idx++) {
		t_mode*	currentMode = this->_mode[idx];
		void (Mode::*func)(t_mode const *, Channel * const , int const) = _modeCmd[currentMode->mode];
		if (func)
			(this->*func)(currentMode, currentChannel, client._clientID);
		else {
			std::string error;
			error[0] = currentMode->mode;
			Send::ToClient(client._clientID, ERR_UNKNOWNMODE(error));
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
