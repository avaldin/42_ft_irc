/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:26:46 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/31 15:34:37 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.class.hpp"

#include "Mode.class.hpp"
#include "Topic.class.hpp"
#include "Invite.class.hpp"
#include "Kick.class.hpp"
#include "Pass.class.hpp"
#include "Nick.class.hpp"
#include "User.class.hpp"
#include "Join.class.hpp"
#include "Privmsg.class.hpp"
#include "Quit.class.hpp"

#include <sstream>
#include <string>
#include <vector>
#include <map>

Parser::Parser( void ) {
	return ;
}

Parser::~Parser( void ) {
	return ;
}

Parser::Parser(std::string const & rawLine) {
	this->_rawLine = rawLine;
	deleteNewline(this->_rawLine);
	this->_cmdMethods["PASS"] = &Parser::setPASS;
	this->_cmdMethods["NICK"] = &Parser::setNICK;
	this->_cmdMethods["USER"] = &Parser::setUSER;
	this->_cmdMethods["JOIN"] = &Parser::setJOIN;
	this->_cmdMethods["KICK"] = &Parser::setKICK;
	this->_cmdMethods["TOPIC"] = &Parser::setTOPIC;
	this->_cmdMethods["MODE"] = &Parser::setMODE;
	this->_cmdMethods["INVITE"] = &Parser::setINVITE;
	this->_cmdMethods["QUIT"] = &Parser::setQUIT;
	this->_cmdMethods["PRIVMSG"] = &Parser::setPRIVMSG;
	this->_command = NULL;
	this->parseRawline();
	return ;
}

void	 Parser::parseRawline( void ) {
	std::stringstream			rawlineStringStream(this->_rawLine);
	std::vector<std::string>	splited;
	std::string					parsed;

	while(std::getline(rawlineStringStream, parsed, ' ')) {
		if (parsed.size())
			splited.push_back(parsed);
	}
	int const size = splited.size();
	if (!size)
		return ;
	int	idx = 0;
	this->_cmdName = splited[idx++];
	std::map<std::string,void(Parser::*)(std::vector<std::string>,int)>::iterator it = _cmdMethods.find(this->_cmdName);
	if (it == _cmdMethods.end())
		return ;
	(this->*(it->second))(splited,idx);
	return ;
}

void	Parser::deleteNewline(std::string& line) {
	int const size = line.size();
	unsigned long	endTextPos;

	if (size && line[size - 1] == '\n')
		line.resize(size - 1);
	if ((endTextPos = this->_rawLine.find('\r')) != std::string::npos)
		this->_rawLine.erase(endTextPos, 1);
	return ;
}

void	Parser::setPASS(std::vector<std::string> splitedLine, int idx) {
	Pass*		newCommand = new Pass();
	int const	size = splitedLine.size();
	
	if (idx < size)
		newCommand->_password = splitedLine[idx];
	this->_command = newCommand;
	return ;
}

void	Parser::setNICK(std::vector<std::string> splitedLine, int idx) {
	int const	size = splitedLine.size();
	Nick*		newCommand = new Nick();
	
	if (idx < size)
		newCommand->_nickname = splitedLine[idx];
	this->_command = newCommand;
	return ;
}

void	Parser::setUSER(std::vector<std::string> splitedLine, int idx) {
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

void	Parser::setJOIN(std::vector<std::string> splitedLine, int idx) {
	int	const			size = splitedLine.size();
	Join*				newCommand = new Join();
	std::string			parsed;
	
	if (idx < size) {
		std::stringstream	channelSS(splitedLine[idx++]);
		while (std::getline(channelSS, parsed, ','))
			newCommand->_targetChannels.push_back(parsed);
	}
	parsed.clear();
	if (idx < size) {
		std::stringstream	keySS(splitedLine[idx++]);
		while (std::getline(keySS, parsed, ','))
			newCommand->_targetKeys.push_back(parsed);
	}
	this->_command = newCommand;
	return ;
}

void	Parser::setKICK(std::vector<std::string> splitedLine, int idx) {
	int const	size = splitedLine.size();
	Kick*		newCommand = new Kick();
	std::string	parsed;
	
	if (idx < size) {
		std::stringstream	channelSS(splitedLine[idx++]);
		while (std::getline(channelSS, parsed, ','))
			newCommand->_targetChannels.push_back(parsed);
	}
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

void	Parser::setTOPIC(std::vector<std::string> splitedLine, int idx) {
	Topic*		newCommand = new Topic();
	int const	size = splitedLine.size();
	
	if (idx < size)
		newCommand->_targetChannel = splitedLine[idx++];
	if (idx < size && splitedLine[idx][0] == ':') {
		splitedLine[idx].erase(0, 1);
		for (;idx < size; idx++)
		{
			if (!newCommand->_topic.empty())
				newCommand->_topic += " ";
			newCommand->_topic += splitedLine[idx];
		}
	}
	else if (idx < size)
		newCommand->_topic = splitedLine[idx];
	this->_command = newCommand;
	return ;
}

void	Parser::setMODE(std::vector<std::string> splitedLine, int idx) {
	Mode*		newCommand = new Mode();
	int const	size = splitedLine.size();

	if (idx < size)
		newCommand->_targetChannel = splitedLine[idx++];
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

void	Parser::setINVITE(std::vector<std::string> splitedLine, int idx) {
	int const	size = splitedLine.size();
	Invite*	newCommand = new Invite();
	
	if (idx < size)
		newCommand->_targetUsers.push_back(splitedLine[idx++]);
	if (idx < size)
		newCommand->_targetChannels.push_back(splitedLine[idx++]);
	this->_command = newCommand;
	return ;
}

void	Parser::setPRIVMSG(std::vector<std::string> splitedLine, int idx) {
	Privmsg*	newCommand = new Privmsg();

	if (splitedLine.size() >= 3) {
		newCommand->_receiver = splitedLine[idx++];
		if (splitedLine[idx][0] == ':') {
			splitedLine[idx].erase(0, 1);
			for (unsigned long i = idx; i < splitedLine.size(); i++)
			{
				if (!newCommand->_message.empty())
					newCommand->_message += " ";
				newCommand->_message += splitedLine[i];
			}
		}
		else
			newCommand->_message = splitedLine[idx];
	}
	this->_command = newCommand;
}

 void	Parser::setQUIT(std::vector<std::string> splitedLine, int idx) {
	Quit*	newCommand = new Quit();

	if (splitedLine.size() >= 2) {
		if (splitedLine[idx][0] == ':') {
			splitedLine[idx].erase(0, 1);
			for (unsigned long i = idx; i < splitedLine.size(); i++)
			{
				if (!newCommand->_message.empty())
					newCommand->_message += " ";
				newCommand->_message += splitedLine[i];
			}
		}
		else
			newCommand->_message = splitedLine[idx];
	}
	this->_command = newCommand;
}

Command* 	Parser::getCommand( void ) {
	return this->_command;
}

