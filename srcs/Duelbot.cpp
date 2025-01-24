/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Duelbot.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:29:20 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/24 06:23:51 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Duelbot.class.hpp"
#include "DuelbotParser.class.hpp"
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

#include <iostream>

std::string	Duelbot::useBot(Client& client, std::string const & line, Channel& test) {
	DuelbotParser	parser(line);
	CommandBot*		cmd = parser.getCommand();

	if (!cmd)
		return "On comprend rien frero";
	return cmd->execute(client, test);
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
		if (it->second && !it->second->_nickname.compare(nickname))
			return true;
	}
	return false;
}

bool	Duelbot::isPlayer(std::string const & nickname) const {
	int const	size = this->_scoreBoard.size();

	std::cout << size << std::endl;
	for (int idx = 0; idx < size; idx++) {
		if (!this->_scoreBoard[idx]->nick.compare(nickname))
			return true;
	}
	return false;	
}

void	Duelbot::createPlayer(std::string const & nickname) {
	t_player*	newPlayer = new t_player;

	std::cout << "starting creation player" << std::endl;
	newPlayer->nick = nickname;
	newPlayer->score = 10;
	this->_scoreBoard.push_back(newPlayer);
	std::cout << "player created" << std::endl;
	return ;
}

void	Duelbot::deletePlayer(std::string const & nickname) {
	for (std::vector<t_player*>::iterator it = this->_scoreBoard.begin(); it != this->_scoreBoard.end(); it++) {
		if ((*it)->nick.compare(nickname)) {
			delete *it;
			this->_scoreBoard.erase(it);
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
	for (std::vector<t_player*>::iterator it = this->_scoreBoard.begin(); it != this->_scoreBoard.end(); it++) {
		if (!this->isClient((*it)->nick))
			this->deletePlayer((*it)->nick);
	}
	return ;
}