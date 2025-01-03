/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:26:46 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/03 13:25:34 by avaldin          ###   ########.fr       */
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
#include "Ping.class.hpp"


#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <iostream>

Command::Command( void ) {
	return ;
}

Command::~Command( void ) {
	return ;
}

Command::Command(std::string const & rawLine) {
	this->_rawLine = rawLine;
	this->_cmdMethods["PASS"] = &Command::setPASS;
	this->_cmdMethods["NICK"] = &Command::setNICK;
	this->_cmdMethods["USER"] = &Command::setUSER;
	// this->_cmdMethods["JOIN"] = &Command::setJOIN;
	this->_cmdMethods["KICK"] = &Command::setKICK;
	this->_cmdMethods["TOPIC"] = &Command::setTOPIC;
	this->_cmdMethods["MODE"] = &Command::setMODE;
	this->_cmdMethods["INVITE"] = &Command::setINVITE;
	// this->_cmdMethods["QUIT"] = &Command::setQUIT;
	this->_cmdMethods["PING"] = &Command::setPING;
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
	if (splited[idx][0] == ':')
		this->_prefix = splited[idx++];
	void(Command::*func)(std::vector<std::string>, int) = _cmdMethods[splited[idx]];
	if (!func)
		return ;
	(this->*func)(splited, idx);
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
	Pass*	newCommand = new Pass();
	
	newCommand->_password = splitedLine[idx];
	this->_command = newCommand;
	return ;
}

void	Command::setNICK(std::vector<std::string> splitedLine, int idx) {
	Nick*	newCommand = new Nick();
	
	newCommand->_nickname = splitedLine[idx];
	this->_command = newCommand;
	return ;
}

void	Command::setUSER(std::vector<std::string> splitedLine, int idx) {
	int const	size = splitedLine.size(); 
	User*		newCommand = new User();

	newCommand->_username = splitedLine[idx++];
	if (idx <= size)
		newCommand->_mode = splitedLine[idx++];
	idx++;
	while (idx >= size)
		newCommand->_realname += (splitedLine[idx++] + " ");
	this->_command = newCommand;
	return ;
}

// void	Command::setJOIN(std::vector<std::string> splitedLine, int idx) {
// 	int	const	size = splitedLine.size();

// 	this->_targetChannels.push_back(splitedLine[idx++]);
// 	if (size > idx)
// 		this->_password = splitedLine[idx];
// 	return ;
// }

void	Command::setKICK(std::vector<std::string> splitedLine, int idx) {
	Kick*		newCommand = new Kick();
	int const	size = splitedLine.size();

	while (size < idx && (splitedLine[idx][0] == '&' || splitedLine[idx][0] == '+' || splitedLine[idx][0] == '!'))
		newCommand->_targetChannels.push_back(splitedLine[idx++]);
	while (size < idx && splitedLine[idx][0] != ':')
		newCommand->_targetUsers.push_back(parseUser(splitedLine[idx++]));
	while (size < idx)
		newCommand->_message += splitedLine[idx++];
	return ;
}

void	Command::setTOPIC(std::vector<std::string> splitedLine, int idx) {
	Topic*		newCommand = new Topic();
	int const	size = splitedLine.size();
	
	newCommand->_targetChannel = splitedLine[idx++];
	while (idx < size)
		newCommand->_topic += splitedLine[idx++];
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
	Invite*	newCommand = new Invite();

	newCommand->_targetUsers.push_back(parseUser(splitedLine[idx++]));
	newCommand->_targetChannels.push_back(splitedLine[idx++]);
	this->_command = newCommand;
	return ;
}

// void	Command::setQUIT(std::vector<std::string> splitedLine, int idx) {
// 	return ;
// }

void	Command::setPING(std::vector<std::string> splitedLine, int idx) {
	Ping*	newCommand = new Ping();
	int 	size = splitedLine.size();

	if (idx <= size)
		newCommand->_token = splitedLine[idx];
	this->_command = newCommand;
}

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
	
