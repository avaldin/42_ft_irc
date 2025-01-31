/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Accept.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 05:17:41 by thibaud           #+#    #+#             */
/*   Updated: 2025/01/24 06:00:45 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	ACCEPT_CLASS_HPP
# define ACCEPT_CLASS_HPP
# include "CommandBot.class.hpp"
# define CHECK_ACCEPT 3

class Client;
class Channel;
class Duelbot;

class Accept : public CommandBot {
public:
	std::string	execute(Client& client, Channel& channel);
	
	std::string const cmdName;

private:
	Accept( void ) : cmdName("Accept") {}
	~Accept( void ) {}

	typedef struct s_data {
		Client*				client;
		Channel*			channel;
		Duelbot*			myBot;
		struct s_player*	p1;
		struct s_player*	p2;
		struct s_duel*		myDuel;
		std::string			error;
		std::string			reply;
	}		t_data;

	void	checkInDuel(t_data& myData);
	void	checkOwnDuel(t_data& myData);
	void	doDuel(t_data& myData);
	
	static void(Accept::*_method[CHECK_ACCEPT])(t_data&);

friend class DuelbotParser;
};

#endif