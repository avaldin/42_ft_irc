/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rank.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 04:23:45 by thibaud           #+#    #+#             */
/*   Updated: 2025/01/24 05:07:04 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	RANK_CLASS_HPP
# define RANK_CLASS_HPP
# include "CommandBot.class.hpp"
# define CHECK_RANK 3

class Client;
class Channel;
class Duelbot;

class Rank : public CommandBot {
public:
	std::string	execute(Client& client, Channel& channel);
	
	std::string const cmdName;

private:
	Rank( void ) : cmdName("RANK") {}
	~Rank( void ) {}

	typedef struct s_data {
		Client*		client;
		Channel*	channel;
		Duelbot*	myBot;
		std::string	error;
		std::string	reply;
	}		t_data;

	std::string	target;

	void	checkClientTarget(t_data& myData);
	void	clientRank(t_data& myData);
	void	targetRank(t_data& myData);
	
	static void(Rank::*_method[CHECK_RANK])(t_data&);

friend class DuelbotParser;
};

#endif
