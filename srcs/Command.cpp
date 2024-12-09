/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:26:46 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/09 18:49:09 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.class.hpp"
#include "Reply.define.hpp"
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
	this->_cmdMethods["JOIN"] = &Command::setJOIN;
	this->_cmdMethods["KICK"] = &Command::setKICK;
	this->_cmdMethods["TOPIC"] = &Command::setTOPIC;
	this->_cmdMethods["MODE"] = &Command::setMODE;
	this->_cmdMethods["INVITE"] = &Command::setINVITE;
	// this->_cmdMethods["QUIT"] = &Command::setQUIT;
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
	this->_command = splited[idx++];
	void (Command::*func)(std::vector<std::string>, int) = _cmdMethods[_command];
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
	this->_password = splitedLine[idx];
	return ;
}

void	Command::setNICK(std::vector<std::string> splitedLine, int idx) {
	t_user	*user = new t_user;

	user->targetNickname = splitedLine[idx];
	return ;
}

void	Command::setUSER(std::vector<std::string> splitedLine, int idx) {
	t_user	*user = new t_user;

	user->targetUsername = splitedLine[idx];
	return ;
}

void	Command::setJOIN(std::vector<std::string> splitedLine, int idx) {
	int	const	size = splitedLine.size();

	this->_targetChannels.push_back(splitedLine[idx++]);
	if (size > idx)
		this->_password = splitedLine[idx];
	return ;
}

void	Command::setKICK(std::vector<std::string> splitedLine, int idx) {
	int const	size = splitedLine.size();

	while (size < idx && (splitedLine[idx][0] == '&' || splitedLine[idx][0] == '+' || splitedLine[idx][0] == '!'))
		this->_targetChannels.push_back(splitedLine[idx++]);
	while (size < idx && splitedLine[idx][0] != ':')
		this->_targetUsers.push_back(parseUser(splitedLine[idx++]));
	while (size < idx)
		this->_message += splitedLine[idx++];
	return ;
}

void	Command::setTOPIC(std::vector<std::string> splitedLine, int idx) {
	int const	size = splitedLine.size();
	
	this->_targetChannels.push_back(splitedLine[idx++]);
	while (idx < size)
		this->_message += splitedLine[idx++];
	return ;
}

void	Command::setMODE(std::vector<std::string> splitedLine, int idx) {
	return ;
}

void	Command::setINVITE(std::vector<std::string> splitedLine, int idx) {
	this->_targetUsers.push_back(parseUser(splitedLine[idx++]));
	this->_targetChannels.push_back(splitedLine[idx++]);
	return ;
}

// void	Command::setQUIT(std::vector<std::string> splitedLine, int idx) {
// 	return ;
// }

std::string 	Command::getPrefix( void ) {
	return this->_prefix;
}

std::string 	Command::getCommand( void ) {
	return this->_command;
}

std::string 	Command::getPassword( void ) {
	return this->_password;
}

std::string 	Command::getMessage( void ) {
	return this->_message;
}

std::vector<std::string>	Command::getTargetChannels( void ) {
	return this->_targetChannels;
}

std::vector<t_user *>	Command::getTargetUsers( void ) {
	return this->_targetUsers;
}
