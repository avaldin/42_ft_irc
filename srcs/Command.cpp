/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:26:46 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/03 23:05:38 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.class.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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
	this->_cmdMethods["QUIT"] = &Command::setQUIT;
	return ;
}

Command::Command(Command const & src) {
	return ;
}

Command& Command::operator=(Command & const rhs) {
	return *this;
}

void	 Command::parseRawline(std::string rawline) {
	std::stringstream			rawlineStringStream(rawline);
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
	if (idx == size)
		return ;
	this->_command = splited[idx];
	return ;
}

void	setPASS(std::vector<std::string> splitedLine, int idx) {
	return ;
}

void	setNICK(std::vector<std::string> splitedLine, int idx) {
	return ;
}

void	setUSER(std::vector<std::string> splitedLine, int idx) {
	return ;
}

void	setJOIN(std::vector<std::string> splitedLine, int idx) {
	return ;
}

void	setKICK(std::vector<std::string> splitedLine, int idx) {
	return ;
}

void	setTOPIC(std::vector<std::string> splitedLine, int idx) {
	return ;	
}

void	setMODE(std::vector<std::string> splitedLine, int idx) {
	return ;
}

void	setINVITE(std::vector<std::string> splitedLine, int idx) {
	return ;
}

void	setQUIT(std::vector<std::string> splitedLine, int idx) {
	return ;
}
