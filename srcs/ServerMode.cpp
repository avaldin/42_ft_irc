/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerMode.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:10:51 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/16 18:42:28 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.class.hpp"
#include "Exception.class.hpp"
#include "Client.class.hpp"
#include "Channel.class.hpp"
#include "Error.define.hpp"
#include "Command.class.hpp"

#include <cstdlib>

Server::Mode::Mode( void ) {
	return ;
}

Server::Mode::~Mode( void ) {
	return ;
}

void	Server::Mode::execute(Server* server, Command* command, int const clientID) {
	
	return ;	
}

void	Server::Mode::MODE(Command* command, int const clientID) {
	std::vector<t_mode*> const	allMode = command->getMode();
	std::string	const			nameTargetChannel = command->getTargetChannels().front();
	Channel * const				currentChannel = this->_server->_serverChannel[nameTargetChannel];
	
	if (!currentChannel) {
		this->_server->sendToClient(this->_server->_mySocket, clientID, ERR_NOSUCHCHANNEL(nameTargetChannel));
		return ;
	}
	std::vector<t_mode*>	allModes = command->getMode();
	std::map<char,void(Server::Mode::*)(t_mode const *, Channel * const , int const)> _modeCmd;
	_modeCmd['t'] = &Server::Mode::MODEt;
	_modeCmd['i'] = &Server::Mode::MODEi;
	_modeCmd['l'] = &Server::Mode::MODEl;
	_modeCmd['k'] = &Server::Mode::MODEk;
	_modeCmd['o'] = &Server::Mode::MODEo;
	int const	size = allModes.size();
	for (int idx = 0; idx < size; idx++) {
		t_mode*	currentMode = allModes[idx];
		void (Server::Mode::*func)(t_mode const *, Channel * const , int const) = _modeCmd[currentMode->mode];
		if (func)
			(this->*func)(currentMode, currentChannel, clientID);
		else {
			std::string error;
			error[0] = currentMode->mode;
			this->_server->sendToClient(this->_server->_mySocket, clientID, ERR_UNKNOWNMODE(error));
		}
	}
}

void	Server::Mode::MODEt(t_mode const * currentMode, Channel * const currentChannel, int const clientID) {
	if (!currentChannel->isOperator(clientID)) {
		this->_server->sendToClient(this->_server->_mySocket, clientID, ERR_CHANOPRIVSNEEDED(currentChannel->_channelName));
		return ;
	}
	currentChannel->_topicMode = currentMode->sign % 5 % 2;
	std::string const	reply = "MODE " + currentChannel->_channelName + static_cast<char>(currentMode->sign) + "t";
	this->_server->sendToChannel(0, currentChannel->_channelName, reply);
	return ;
}

void	Server::Mode::MODEi(t_mode const * currentMode, Channel * const currentChannel, int const clientID) {
	if (!currentChannel->isOperator(clientID)) {
		this->_server->sendToClient(this->_server->_mySocket, clientID, ERR_CHANOPRIVSNEEDED(currentChannel->_channelName));
		return ;
	}
	currentChannel->_inviteOnlyMode = currentMode->sign % 5 % 2;
	std::string const	reply = "MODE " + currentChannel->_channelName + static_cast<char>(currentMode->sign) + "i";
	this->_server->sendToChannel(0, currentChannel->_channelName, reply);
	return ;
}

void	Server::Mode::MODEl(t_mode const * currentMode, Channel * const currentChannel, int const clientID) {
	if (!currentChannel->isOperator(clientID)) {
		this->_server->sendToClient(this->_server->_mySocket, clientID, ERR_CHANOPRIVSNEEDED(currentChannel->_channelName));
		return ;
	}
	std::string reply = "MODE " + currentChannel->_channelName + static_cast<char>(currentMode->sign) + "l";
	if (currentMode->sign == '+') {
		currentChannel->_channelLimit = std::atoi(currentMode->args.c_str());
		reply += (" " + currentMode->args);
	}
	else if (currentMode->sign == '-')
		currentChannel->_channelLimit = -1;
	this->_server->sendToChannel(0, currentChannel->_channelName, reply);
	return ;
}

void	Server::Mode::MODEk(t_mode const * currentMode, Channel * const currentChannel, int const clientID) {
	if (!currentChannel->isOperator(clientID)) {
		this->_server->sendToClient(this->_server->_mySocket, clientID, ERR_CHANOPRIVSNEEDED(currentChannel->_channelName));
		return ;
	}
	if (currentMode->sign == '+')
		currentChannel->_channelPassword = currentMode->args;
	else if (currentMode->sign == '-')
		currentChannel->_channelPassword = "";
	std::string const	reply = "MODE " + currentChannel->_channelName + static_cast<char>(currentMode->sign) + "k";
	this->_server->sendToChannel(0, currentChannel->_channelName, reply);
	return ;
}

void	Server::Mode::MODEo(t_mode const * currentMode, Channel * const currentChannel, int const clientID) {
	if (!currentChannel->isOperator(clientID)) {
		this->_server->sendToClient(this->_server->_mySocket, clientID, ERR_CHANOPRIVSNEEDED(currentChannel->_channelName));
		return ;
	}
	int const	targetID = std::atoi(currentMode->args.c_str());
	if (!currentChannel->isClient(targetID)) {
		this->_server->sendToClient(this->_server->_mySocket, clientID, ERR_USERNOTINCHANNEL(currentMode->args, currentChannel->_channelName));
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
	this->_server->sendToChannel(0, currentChannel->_channelName, reply);
	return ; 
}
