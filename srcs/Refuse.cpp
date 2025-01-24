/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Refuse.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 05:46:37 by thibaud           #+#    #+#             */
/*   Updated: 2025/01/24 06:18:53 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Refuse.class.hpp"

#include "Duelbot.class.hpp"
#include "BotError.define.hpp"
#include "Channel.class.hpp"
#include "Client.class.hpp"

void(Refuse::*Refuse::_method[CHECK_REFUSE])(t_data&) = {
	&Refuse::checkInDuel,
	&Refuse::cancelDuel
};

std::string	Refuse::execute(Client& client, Channel& channel) {
	t_data	myData;
	int		idx;

	myData.client = &client;
	myData.channel = &channel;
	myData.myBot = channel._myBot;
	for (idx = 0; idx < CHECK_REFUSE && myData.error.empty(); idx++)
		(this->*_method[idx])(myData);
	if (!myData.error.empty())
		return myData.error;
	return myData.reply;
}

void	Refuse::checkInDuel(t_data& myData) {
	if (!myData.myBot->isPlayer(myData.client->_nickname) || !myData.myBot->isInDuel(myData.myBot->findPlayer(myData.client->_nickname)))
		myData.error = BOTERR_NOTINDUEL(myData.client->_nickname);
	return ;
}

void	Refuse::cancelDuel(t_data& myData) {
	t_duel*	myDuel = myData.myBot->findDuel(myData.myBot->findPlayer(myData.client->_nickname));
	
	myData.myBot->deleteDuel(myDuel);
	myData.reply = myData.client->_nickname + " refused the duel";
	return ;
}
