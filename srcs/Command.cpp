/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:26:46 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/02 19:36:54 by tmouche          ###   ########.fr       */
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
	for (int idx = 0; idx < size; idx++) {
		if (idx == 0 && splited[idx][0] == ':') {
			this->_prefix = splited[idx];
		}
		else {
			if (idx == 0 || idx == 1)
				this->_command = splited[idx];
			else if (this->_message.empty() && splited[idx][0] != ':')
				this->_arguments.push_back(splited[idx]);
			else {
				this->_message += "";
				this->_message += splited[idx];
			}
		}
	}
	return ;
}

std::string*	Command::getPrefix( void ) {
	return &this->_prefix;
}

std::string*	Command::getCommand( void ) {
	return &this->_command;
}

std::string*	Command::getMessage( void ) {
	return &this->_message;
}

std::vector<std::string>*	Command::getArgs( void ) {
	return &this->_arguments;
}

