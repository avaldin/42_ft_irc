/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rank.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:23:29 by thibaud           #+#    #+#             */
/*   Updated: 2025/01/24 18:23:26 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Rank.class.hpp"

#include "Duelbot.class.hpp"
#include "BotError.define.hpp"
#include "Channel.class.hpp"
#include "Client.class.hpp"

#include <sstream>

void(Rank::*Rank::_method[CHECK_RANK])(t_data&) = {
	&Rank::checkClientTarget,
	&Rank::clientRank,
	&Rank::targetRank
};

std::string	Rank::execute(Client& client, Channel& channel) {
	t_data	myData;
	int		idx;

	myData.client = &client;
	myData.channel = &channel;
	myData.myBot = &channel._myBot;	
	for (idx = 0; idx < CHECK_RANK && myData.error.empty(); idx++)
		(this->*_method[idx])(myData);
	if (!myData.error.empty())
		return myData.error;
	return myData.reply;
}

void	Rank::checkClientTarget(t_data& myData) {
	if (!this->target.empty() && (!myData.channel->isClient(this->target)))
		myData.error = BOTERR_USERNOTVALID(this->target);
	return ;
}

void	Rank::clientRank(t_data& myData) {

	if (!this->target.empty())
		return ;
	if (myData.myBot->isPlayer(myData.client->_nickname)) {
		int const	size = myData.myBot->_scoreBoard.size();
		int			idx;
		for (idx = 0; idx < size; idx++) {
			if (!myData.myBot->_scoreBoard[idx]->nick.compare(myData.client->_nickname))
				break ;
		}
		std::stringstream	ss;
		ss << myData.client->_nickname << " is classed " << ++idx << " with " << myData.myBot->findPlayer(myData.client->_nickname)->score << "pts";
		myData.reply = ss.str(); 
	}
	else
		myData.error = BOTERR_NOTAPLAYER(myData.client->_nickname);
	return ;	
}

void	Rank::targetRank(t_data& myData) {

	if (this->target.empty())
		return ;
	if (myData.myBot->isPlayer(this->target)) {
		int const	size = myData.myBot->_scoreBoard.size();
		int			idx;
		for (idx = 0; idx < size; idx++) {
			if (!myData.myBot->_scoreBoard[idx]->nick.compare(this->target))
				break ;
		}
		std::stringstream	ss;
		ss << this->target << " is classed " << ++idx << " with " << myData.myBot->findPlayer(this->target)->score << "pts";
		myData.reply = ss.str(); 
	}
	else
		myData.error = BOTERR_NOTAPLAYER(this->target);
	return ;
}