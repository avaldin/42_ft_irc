/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scoreboard.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 06:01:35 by thibaud           #+#    #+#             */
/*   Updated: 2025/01/24 06:04:54 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scoreboard.class.hpp"

#include "Duelbot.class.hpp"
#include "BotError.define.hpp"
#include "Channel.class.hpp"
#include "Client.class.hpp"

#include <sstream>
#include <stdlib.h>
#include <time.h>

void(Scoreboard::*Scoreboard::_method[CHECK_SCOREBOARD])(t_data&) = {};

std::string	Scoreboard::execute(Client& client, Channel& channel) {
	t_data	myData;
	int		idx;

	myData.client = &client;
	myData.channel = &channel;
	myData.myBot = channel._myBot;
	for (idx = 0; idx < CHECK_SCOREBOARD && myData.error.empty(); idx++)
		(this->*_method[idx])(myData);
	if (!myData.error.empty())
		return myData.error;
	return myData.reply;
}

void	Scoreboard::displayScore(t_data& myData) {
	int const			size = myData.myBot->_scoreBoard.size();
	std::stringstream	ss;
	(void)myData;
	
	ss << "your top3 are:";
	for (int idx = 0; idx < 3 && idx < size; idx++) {
		t_player*	actPlayer = myData.myBot->_scoreBoard[idx];
		ss << std::endl << "Top" << idx + 1 << ": " << actPlayer->nick  << " with " << actPlayer->score << "pts";
	}
	myData.reply = ss.str();
	return ;
}