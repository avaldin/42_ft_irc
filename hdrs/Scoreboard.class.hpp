/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scoreboard.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 05:56:50 by thibaud           #+#    #+#             */
/*   Updated: 2025/01/24 06:07:49 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SCOREBOARD_CLASS_HPP
# define SCOREBOARD_CLASS_HPP
# include "CommandBot.class.hpp"
# define CHECK_SCOREBOARD 1

class Client;
class Channel;
class Duelbot;

class Scoreboard : public CommandBot {
public:
	std::string	execute(Client& client, Channel& channel);
	
	std::string const cmdName;

private:
	Scoreboard( void ) : cmdName("Scoreboard") {}
	~Scoreboard( void ) {}

	typedef struct s_data {
		Client*		client;
		Channel*	channel;
		Duelbot*	myBot;
		std::string	error;
		std::string	reply;
	}		t_data;

	void	displayScore(t_data& myData);
	
	static void(Scoreboard::*_method[CHECK_SCOREBOARD])(t_data&);

friend class DuelbotParser;
};

#endif