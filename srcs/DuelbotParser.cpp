/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DuelbotParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:38:53 by thibaud           #+#    #+#             */
/*   Updated: 2025/01/24 19:36:39 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DuelbotParser.class.hpp"

#include "Duel.class.hpp"
#include "Rank.class.hpp"
#include "Accept.class.hpp"
#include "Refuse.class.hpp"
#include "Scoreboard.class.hpp"
#include <sstream>

DuelbotParser::DuelbotParser(std::string const & rawline) {
	this->_rawline = rawline;
	this->_command = NULL;
	this->_cmdMethods["DUEL"] = &DuelbotParser::setDuel;
	this->_cmdMethods["RANK"] = &DuelbotParser::setRank;
	this->_cmdMethods["SCOREBOARD"] = &DuelbotParser::setScoreboard;
	this->_cmdMethods["ACCEPT"] = &DuelbotParser::setAccept;
	this->_cmdMethods["REFUSE"] = &DuelbotParser::setRefuse;
	this->parseRawline();
	return ;
}

void	DuelbotParser::parseRawline( void ) {
	std::stringstream			rawlineSS(this->_rawline);
	std::vector<std::string>	splited;
	std::string					parsed;

	while(std::getline(rawlineSS, parsed, ' ')) {
		if (parsed.size())
			splited.push_back(parsed);
	}
	int const size = splited.size();
	if (size < 2)
		return ;
	this->botName = splited[0];
	this->cmdName = splited[1];
	std::map<std::string,void(DuelbotParser::*)(std::vector<std::string>, int)>::iterator	it;
	it = this->_cmdMethods.find(this->cmdName);
	if (it == this->_cmdMethods.end())
		return ;
	(this->*(it->second))(splited, 2);
	return ;
}

void	DuelbotParser::setDuel(std::vector<std::string> splited, int idx) {
	int const	size = splited.size();
	Duel*		newCmd = new Duel;

	if (idx < size)
		newCmd->target = splited[idx++];
	if (idx < size) {
		std::stringstream	ssBet(splited[idx]);
		ssBet >> newCmd->bet;
	}
	this->_command = newCmd;
	return ;
}

void	DuelbotParser::setRank(std::vector<std::string> splited, int idx) {
	int const	size = splited.size();
	Rank*		newCmd = new Rank;

	if (idx < size)
		newCmd->target = splited[idx];
	this->_command = newCmd;
	return ;
}

void	DuelbotParser::setAccept(std::vector<std::string> splited, int idx) {
	Accept*	newCmd = new Accept;

	(void)splited;
	(void)idx;
	this->_command = newCmd;
	return ;
}

void	DuelbotParser::setRefuse(std::vector<std::string> splited, int idx) {
	Refuse*	newCmd = new Refuse;

	(void)splited;
	(void)idx;
	this->_command = newCmd;
	return ;
}

void	DuelbotParser::setScoreboard(std::vector<std::string> splited, int idx) {
	Scoreboard*	newCmd = new Scoreboard;

	(void)splited;
	(void)idx;
	this->_command = newCmd;
	return ;	
}

CommandBot*	DuelbotParser::getCommand( void ) {
	return this->_command;
}