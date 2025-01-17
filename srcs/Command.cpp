/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:26:46 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/17 11:52:31 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.class.hpp"
#include "Reply.define.hpp"

#include "Mode.class.hpp"
#include "Topic.class.hpp"
#include "Invite.class.hpp"
#include "Kick.class.hpp"
#include "Pass.class.hpp"
#include "Nick.class.hpp"
#include "User.class.hpp"
#include "Join.class.hpp"
#include "Privmsg.class.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <iostream>

#include <stdio.h>

Command::Command( void ) {
	return ;
}

Command::~Command( void ) {
	return ;
}

Command::Command(std::string const & rawLine) {
	this->_rawLine = rawLine;
	deleteNewline(this->_rawLine);
	this->_cmdMethods["PASS"] = &Command::setPASS;
	this->_cmdMethods["NICK"] = &Command::setNICK;
	this->_cmdMethods["USER"] = &Command::setUSER;
	this->_cmdMethods["JOIN"] = &Command::setJOIN;
	this->_cmdMethods["KICK"] = &Command::setKICK;
	this->_cmdMethods["TOPIC"] = &Command::setTOPIC;
	this->_cmdMethods["MODE"] = &Command::setMODE;
	this->_cmdMethods["INVITE"] = &Command::setINVITE;
	// this->_cmdMethods["QUIT"] = &Command::setQUIT;
	this->_cmdMethods["PRIVMSG"] = &Command::setPRIVMSG;
	this->_command = NULL;
	this->parseRawline();
	return ;
}

Command::Command(Command const & src) {
	(void)src;
	return ;
}

Command& Command::operator=(Command const & rhs) {
	(void)rhs;
	return *this;
}

void	 Command::parseRawline( void ) {
	std::stringstream			rawlineStringStream(this->_rawLine);
	std::vector<std::string>	splited;
	std::string					parsed;

	while(std::getline(rawlineStringStream, parsed, ' ')) {
		splited.push_back(parsed);
	}
	int const size = splited.size();
	if (!size)
		return ;
	int	idx = 0;
	// if (splited[idx][0] == ':')
	// 	this->_prefix = splited[idx++];
	this->_cmdName = splited[idx++];
	void(Command::*func)(std::vector<std::string>, int) = NULL;
	func = _cmdMethods[this->_cmdName];
	if (!func)
		return ;
	(this->*func)(splited, idx);
	return ;
}

void	Command::deleteNewline(std::string& line) {
	int const size = line.size();
	unsigned long	endTextPos;

	if (size && line[size - 1] == '\n')
		line.resize(size - 1);
	if ((endTextPos = this->_rawLine.find('\r')) != std::string::npos)
		this->_rawLine.erase(endTextPos, 1);
	return ;
}

t_user	*Command::parseUser(std::string user) {
	int			idx = 0;
	int const	size = user.size();
	t_user*		userStruct = new t_user;
	
	while (idx < size && user[idx] != '!')
		userStruct->targetNickname += user[idx++];
	if (user[idx] == '!')
		++idx;
	while (idx < size && user[idx] != '@')
		userStruct->targetUsername += user[idx++];
	if (user[idx] == '@')
		++idx;
	while (idx < size)
		userStruct->targetServer += user[idx++];
	return userStruct;
}

void	Command::setPASS(std::vector<std::string> splitedLine, int idx) {
	Pass*		newCommand = new Pass();
	int const	size = splitedLine.size();
	
	if (idx < size)
		newCommand->_password = splitedLine[idx];
	this->_command = newCommand;
	return ;
}

void	Command::setNICK(std::vector<std::string> splitedLine, int idx) {
	int const	size = splitedLine.size();
	Nick*		newCommand = new Nick();
	
	if (idx < size)
		newCommand->_nickname = splitedLine[idx];
	this->_command = newCommand;
	return ;
}

void	Command::setUSER(std::vector<std::string> splitedLine, int idx) {
	int const	size = splitedLine.size(); 
	User*		newCommand = new User();

	if (idx < size)
		newCommand->_username = splitedLine[idx++];
	if (idx < size)
		newCommand->_mode = splitedLine[idx++];
	idx++; // for the unused param
	while (idx < size)
		newCommand->_realname += (splitedLine[idx++] + " ");
	this->_command = newCommand;
	return ;
}

void	Command::setJOIN(std::vector<std::string> splitedLine, int idx) {
	int	const			size = splitedLine.size();
	Join*				newCommand = new Join();
	std::string			parsed;

	std::stringstream	channelSS(splitedLine[idx++]);
	while (std::getline(channelSS, parsed, ','))
		newCommand->_targetChannels.push_back(parsed);
	parsed.clear();
	if (idx < size) {
		std::stringstream	keySS(splitedLine[idx++]);
		while (std::getline(keySS, parsed, ','))
			newCommand->_targetKeys.push_back(parsed);
	}
	this->_command = newCommand;
	return ;
}

void	Command::setKICK(std::vector<std::string> splitedLine, int idx) {
	int const	size = splitedLine.size();
	Kick*		newCommand = new Kick();
	std::string	parsed;
	
	std::stringstream	channelSS(splitedLine[idx++]);
	while (std::getline(channelSS, parsed, ','))
		newCommand->_targetChannels.push_back(parsed);
	parsed.clear();
	if (idx < size) {
		std::stringstream	targetSS(splitedLine[idx++]);
		while (std::getline(targetSS, parsed, ','))
			newCommand->_targetUsers.push_back(parsed);
		while (idx < size)
			newCommand->_message += (splitedLine[idx++] + " ");
	}
	this->_command = newCommand;
	return ;
}

void	Command::setTOPIC(std::vector<std::string> splitedLine, int idx) {
	Topic*		newCommand = new Topic();
	int const	size = splitedLine.size();
	
	if (idx < size)
		newCommand->_targetChannel = splitedLine[idx++];
	while (idx < size)
		newCommand->_topic += (splitedLine[idx++] + " ");
	this->_command = newCommand;
	return ;
}

void	Command::setMODE(std::vector<std::string> splitedLine, int idx) {
	Mode*		newCommand = new Mode();
	int const	size = splitedLine.size();

	for (;idx < size; idx++) {
		if (splitedLine[idx][0] == '+' || splitedLine[idx][0] == '-') {
			unsigned int	sign = splitedLine[idx][0]; 
			for (int idxWord = 1; splitedLine[idx][idxWord]; idxWord++) {
				t_mode	*newMode = new t_mode;
				newMode->sign = sign;
				newMode->mode = splitedLine[idx][idxWord];
				newCommand->_mode.push_back(newMode);
			}
		}
		else if (!newCommand->_mode.empty() && newCommand->_mode.back()->args.empty())
			newCommand->_mode.back()->args = splitedLine[idx];
	}
	this->_command = newCommand;
	return ;
}

void	Command::setINVITE(std::vector<std::string> splitedLine, int idx) {
	int const	size = splitedLine.size();
	Invite*	newCommand = new Invite();
	
	if (idx < size)
		newCommand->_targetUsers.push_back(splitedLine[idx++]);
	if (idx < size)
		newCommand->_targetChannels.push_back(splitedLine[idx++]);
	this->_command = newCommand;
	return ;
}

void	Command::setPRIVMSG(std::vector<std::string> splitedLine, int idx) {
	Privmsg*	newCommand = new Privmsg();

	if (splitedLine.size() >= 3) {
		newCommand->_receiver = splitedLine[idx++];
		if (splitedLine[idx][0] == ':') {
			splitedLine[idx].erase(0);
			for (std::vector<std::string>::iterator it = splitedLine.begin() + 1; it != splitedLine.end() ; ++it)
				newCommand->_message += *it;
		}
		else
			newCommand->_message = splitedLine[idx];
	}
	this->_command = newCommand;
}

// void	Command::setQUIT(std::vector<std::string> splitedLine, int idx) {
// 	return ;
// }

std::string 	Command::getPrefix( void ) {
	return this->_prefix;
}

ACommand* 	Command::getCommand( void ) {
	return this->_command;
}

// std::string 	Command::getPassword( void ) {
// 	return this->_password;
// }

// std::string 	Command::getMessage( void ) {
// 	return this->_message;
// }

// std::vector<std::string&>&	Command::getTargetChannels( void ) {
// 	return this->_targetChannels;
// }

// std::vector<t_user*>	Command::getTargetUsers( void ) {
// 	return this->_targetUsers;
// }
	
