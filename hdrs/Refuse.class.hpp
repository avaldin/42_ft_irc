/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Refuse.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 05:44:37 by thibaud           #+#    #+#             */
/*   Updated: 2025/01/24 06:08:05 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	REFUSE_CLASS_HPP
# define REFUSE_CLASS_HPP
# include "CommandBot.class.hpp"
# define CHECK_REFUSE 2

class Client;
class Channel;
class Duelbot;

class Refuse : public CommandBot {
public:
	std::string	execute(Client& client, Channel& channel);
	
	std::string const cmdName;

private:
	Refuse( void ) : cmdName("Refuse") {}
	~Refuse( void ) {}

	typedef struct s_data {
		Client*		client;
		Channel*	channel;
		Duelbot*	myBot;
		std::string	error;
		std::string	reply;
	}		t_data;

	void	checkInDuel(t_data& myData);
	void	cancelDuel(t_data& myData);
	
	static void(Refuse::*_method[CHECK_REFUSE])(t_data&);

friend class DuelbotParser;
};

#endif