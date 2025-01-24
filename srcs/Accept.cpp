/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Accept.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 05:19:04 by thibaud           #+#    #+#             */
/*   Updated: 2025/01/24 19:04:45 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Accept.class.hpp"

#include "Duelbot.class.hpp"
#include "BotError.define.hpp"
#include "Channel.class.hpp"
#include "Client.class.hpp"

#include <sstream>
#include <stdlib.h>
#include <time.h>

void(Accept::*Accept::_method[CHECK_ACCEPT])(t_data&) = {
	&Accept::checkInDuel,
	&Accept::checkOwnDuel,
	&Accept::doDuel
};

std::string	Accept::execute(Client& client, Channel& channel) {
	t_data	myData;
	int		idx;

	myData.client = &client;
	myData.channel = &channel;
	myData.myBot = &channel._myBot;
	for (idx = 0; idx < CHECK_ACCEPT && myData.error.empty(); idx++)
		(this->*_method[idx])(myData);
	if (!myData.error.empty())
		return myData.error;
	return myData.reply;
}

void	Accept::checkInDuel(t_data& myData) {
	if (!myData.myBot->isPlayer(myData.client->_nickname) || !myData.myBot->isInDuel(myData.myBot->findPlayer(myData.client->_nickname)))
		myData.error = BOTERR_NOTINDUEL(myData.client->_nickname);
	return ;
}

void	Accept::checkOwnDuel(t_data& myData) {
	myData.p2 = myData.myBot->findPlayer(myData.client->_nickname);
	myData.myDuel = myData.myBot->findDuel(myData.p2);

	if (myData.myDuel->opponent1 == myData.p2)
		myData.error = BOTERR_DUELHIMSELF(myData.client->_nickname);
	myData.p1 = myData.myDuel->opponent1;
	return ;
}

void	Accept::doDuel(t_data& myData) {
	t_player * const	players[2] = {myData.p1, myData.p2};
	
	srand(time(NULL));
	unsigned int const	result = static_cast<unsigned int>(rand()) % 2;
	players[result]->score += myData.myDuel->bet;
	players[(result + 1) % 2]->score -= myData.myDuel->bet;
	std::stringstream	ss;
	ss << players[result]->nick << " ANNIHILATE " << players[(result + 1) % 2]->nick << " FOR " << myData.myDuel->bet << "pts";
	myData.myBot->deleteDuel(myData.myDuel);
	myData.reply = ss.str();
	return ;
}
