/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Duelbot.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:29:20 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/25 17:42:55 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Duelbot.class.hpp"
#include "DuelbotParser.class.hpp"
#include "BotError.define.hpp"
#include "Send.namespace.hpp"
#include "Client.class.hpp"
#include "Duel.class.hpp"
#include "Rank.class.hpp"
#include "Accept.class.hpp"
#include "Refuse.class.hpp"
#include "Scoreboard.class.hpp"
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include <iostream>

std::string	Duelbot::useBot(Client& client, std::string const & line, Channel& channel) {
	DuelbotParser	parser(line);
	CommandBot*		cmd = parser.getCommand();
	std::string		botMessage;

	this->_myChannel = &channel;
	if (this->isPlayer(client._nickname))
		this->findPlayer(client._nickname)->score += 1;
	if (parser.botName[0] == '!' && parser.botName.compare(this->name))
		botMessage = BOTERR_UNKNOWNBOT(parser.botName);
	else if (parser.botName[0] == '!' && !cmd) 
		botMessage = BOTERR_UNKNOWNCOMMAND(parser.cmdName);
	else if (parser.botName[0] == '!') {
		botMessage = cmd->execute(client, channel);
		delete cmd;
	}
	this->updateDb();
	this->sortScoreBoard();
	return botMessage;
}

void	Duelbot::sortScoreBoard( void ) {
	int const	size = this->_scoreBoard.size();

	for (int temp = 0; temp < size; temp++) {
		for (int idx = 0; idx < size - 1; idx++) {
			if (this->_scoreBoard[idx]->score < this->_scoreBoard[idx + 1]->score) {
				t_player*	pTemp = this->_scoreBoard[idx];
				this->_scoreBoard[idx] = this->_scoreBoard[idx + 1];
				this->_scoreBoard[idx + 1] = pTemp;
			}
		}
	}
	return ;
}

void	Duelbot::deleteDuel(t_duel* myDuel) {
	for (std::vector<t_duel*>::iterator it = this->_pendingDuel.begin(); it != this->_pendingDuel.end(); it++) {
		if (myDuel == *it) {
			this->_pendingDuel.erase(it);
			delete myDuel;
			return ;
		}
	}
	return ;
}

bool	Duelbot::isClient(std::string const & nickname) const {
	for (std::map<int, Client const *>::const_iterator it = this->_myChannel->_channelClient.begin(); it != this->_myChannel->_channelClient.end(); it++) {
		if (it->second && !it->second->_nickname.compare(nickname)) {
			return true;
		}
	}
	return false;
}

bool	Duelbot::isPlayer(std::string const & nickname) const {
	int const	size = this->_scoreBoard.size();

	for (int idx = 0; idx < size; idx++) {
		if (!this->_scoreBoard[idx]->nick.compare(nickname))
			return true;
	}
	return false;	
}

void	Duelbot::createPlayer(std::string const & nickname) {
	t_player*	newPlayer = new t_player;

	newPlayer->nick = nickname;
	newPlayer->score = 10;
	this->_scoreBoard.push_back(newPlayer);
	return ;
}

void	Duelbot::deletePlayer(std::string const & nickname) {
	for (std::vector<t_player*>::iterator it = this->_scoreBoard.begin(); it != this->_scoreBoard.end(); it++) {
		if ((*it)->nick.compare(nickname)) {
			if (this->isInDuel(*it))
				this->deleteDuel(this->findDuel(*it));
			this->_scoreBoard.erase(it);
			delete *it;
			break ;
		}

	}
	return ;
}

t_player*	Duelbot::findPlayer(std::string const & nickname) const {
	int const	size = this->_scoreBoard.size();

	for (int idx = 0; idx < size; idx++) {
		if (!this->_scoreBoard[idx]->nick.compare(nickname))
			return this->_scoreBoard[idx];
	}
	return NULL;
}

bool	Duelbot::isInDuel(t_player* player) const {
	for (std::vector<t_duel*>::const_iterator it = this->_pendingDuel.begin(); it != this->_pendingDuel.end(); it++) {
		if ((*it)->opponent1 == player || (*it)->opponent2 == player)
			return true;
	}
	return false;
}

t_duel*	Duelbot::findDuel(t_player* player) const {
	for (std::vector<t_duel*>::const_iterator it = this->_pendingDuel.begin(); it != this->_pendingDuel.end(); it++) {
	if ((*it)->opponent1 == player || (*it)->opponent2 == player)
		return *it;
	}
	return NULL;
}

void	Duelbot::updateDb( void ) {
	int	size = this->_scoreBoard.size();
	for (int idx = 0; idx < size; idx++) {
		std::cout << this->_scoreBoard[idx] << std::endl;
		if (this->_scoreBoard[idx] && !this->isClient(this->_scoreBoard[idx]->nick)) {
			this->deletePlayer(this->_scoreBoard[idx]->nick);
			break ;
		}
	}
	return ;
}