/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Duel.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:55:07 by thibaud           #+#    #+#             */
/*   Updated: 2025/01/24 06:29:20 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUEL_CLASS_HPP
# define DUEL_CLASS_HPP
# include "CommandBot.class.hpp"
# define CHECK_DUEL 8

class Client;
class Channel;
class Duelbot;

class Duel : public CommandBot {
public:
	std::string	execute(Client& client, Channel& channel);
	
	std::string const	cmdName;

private:
	Duel( void ) : cmdName("DUEL") {}
	~Duel( void ) {}
	
	typedef struct	s_data {
		Client*		client;
		Channel*	channel;
		Duelbot*	myBot;
		struct s_player*	p1;
		struct s_player*	p2;
		std::string	error;
		std::string reply;
	}		t_data;
	
	void	checkParams(t_data& myData);
	void	checkClientTarget(t_data& myData);
	void	checkPlayer(t_data& myData);
	void	checkOpponent(t_data& myData);
	void	checkInDuel(t_data& myData);
	void	checkScore(t_data& myData);
	void	getInstancePlayer(t_data& myData);
	void	createDuel(t_data& myData);

	std::string		target;
	unsigned int	bet;

	static void(Duel::*_method[CHECK_DUEL])(t_data&);

friend class DuelbotParser;
};

#endif
