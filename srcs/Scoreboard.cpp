/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scoreboard.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 06:01:35 by thibaud           #+#    #+#             */
/*   Updated: 2025/01/24 18:44:40 by tmouche          ###   ########.fr       */
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

#include <iostream>

void(Scoreboard::*Scoreboard::_method[CHECK_SCOREBOARD])(t_data&) = {
	&Scoreboard::displayScore
};

std::string	Scoreboard::execute(Client& client, Channel& channel) {
	t_data	myData;
	int		idx;

	myData.client = &client;
	myData.channel = &channel;
	myData.myBot = &channel._myBot;
	for (idx = 0; idx < CHECK_SCOREBOARD && myData.error.empty(); idx++)
		(this->*_method[idx])(myData);
	if (!myData.error.empty())
		return myData.error;
	return myData.reply;
}

void	Scoreboard::displayScore(t_data& myData) {
	int const			size = myData.myBot->_scoreBoard.size();
	std::stringstream	ss;
	
	ss << "your top3 are:";
	for (int idx = 0; idx < 3 && idx < size; idx++)
		ss << " -Top" << idx + 1 << ": " << myData.myBot->_scoreBoard[idx]->nick  << " (" << myData.myBot->_scoreBoard[idx]->score << "pts)";
	myData.reply = ss.str();
	return ;
}