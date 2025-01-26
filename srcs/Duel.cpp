/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Duel.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:54:43 by thibaud           #+#    #+#             */
/*   Updated: 2025/01/24 18:34:18 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Duel.class.hpp"

#include "Duelbot.class.hpp"
#include "BotError.define.hpp"
#include "Channel.class.hpp"
#include "Client.class.hpp"

#include <sstream>

void(Duel::*Duel::_method[CHECK_DUEL])(t_data&) = {
	&Duel::checkParams,
	&Duel::checkClientTarget,
	&Duel::checkPlayer,
	&Duel::getInstancePlayer,
	&Duel::checkOpponent, 
	&Duel::checkInDuel,
	&Duel::checkScore,
	&Duel::createDuel};

std::string	Duel::execute(Client& client, Channel& channel) {
	t_data	myData;
	int		idx;

	myData.client = &client;
	myData.channel = &channel;
	myData.myBot = &channel._myBot;
	for (idx = 0; idx < CHECK_DUEL && myData.error.empty(); idx++)
		(this->*_method[idx])(myData);
	if (!myData.error.empty())
		return myData.error;
	return myData.reply;
}

void	Duel::checkParams(t_data& myData) {
	if (this->target.empty() || !this->bet)
		myData.error = BOTERR_NEEDMOREPARAMS(this->cmdName);
	return ;
}

void	Duel::checkClientTarget(t_data& myData) {
	if (!myData.channel->isClient(this->target))
		myData.error = BOTERR_USERNOTVALID(this->target);
	return ;
}

void	Duel::checkPlayer(t_data& myData) {
	if (!myData.myBot->isPlayer(myData.client->_nickname))
		myData.myBot->createPlayer(myData.client->_nickname);
	if (!myData.myBot->isPlayer(this->target))
		myData.myBot->createPlayer(this->target);
	return ;
}

void	Duel::checkOpponent(t_data& myData) {
	if (myData.p1 == myData.p2)
		myData.error = BOTERR_USERNOTVALID(myData.p1->nick);
	return ;	
}

void	Duel::checkInDuel(t_data& myData) {
	if (myData.myBot->isInDuel(myData.p1) || myData.myBot->isInDuel(myData.p2))
		myData.error = BOTERR_DUELNOTVALID;
	return ;
}

void	Duel::checkScore(t_data& myData) {
	if (myData.p1->score < this->bet || myData.p2->score < this->bet)
		myData.error = BOTERR_DUELNOTVALID;
	return ;
}

void	Duel::getInstancePlayer(t_data& myData) {
	myData.p1 = myData.myBot->findPlayer(myData.client->_nickname);
	myData.p2 = myData.myBot->findPlayer(this->target);
	return ;
}

void	Duel::createDuel(t_data& myData) {
	t_duel*	newDuel = new t_duel;
	newDuel->opponent1 = myData.p1;
	newDuel->opponent2 = myData.p2;
	newDuel->bet = this->bet;
	myData.myBot->_pendingDuel.push_back(newDuel);
	std::stringstream	ss;
	ss << myData.client->_nickname << " provoke " << this->target << " to a duel for " << this->bet << "pts! (!duelbot ACCEPT/REFUSE)";
	myData.reply = ss.str();
	return ;
}