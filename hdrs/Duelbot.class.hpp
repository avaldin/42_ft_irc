/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Duelbot.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:54:44 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/27 17:14:57 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUELBOT_CLASS_HPP
# define DUELBOT_CLASS_HPP
# include <string>
# include <vector>
# include <map>

class Client;
class Channel;

typedef struct s_player {
	std::string		nick;
	unsigned int	score;		
}	t_player;

typedef struct s_duel {
	t_player*		opponent1;
	t_player*		opponent2;
	unsigned int	bet;
}	t_duel;

class Duelbot {
public:
	Duelbot( void ) : name("!duelbot") {}
	~Duelbot( void );

	std::string	useBot(Client&, std::string const &, Channel&);

	std::string const	name;
	
private:
	typedef struct	s_data {
		std::string					client;
		std::string					target;
		unsigned int				bet;
		std::vector<std::string>	splited;
		std::string					error;
		std::string					message;
		t_duel*						myDuel;
	}				t_data;
	
	void		sortScoreBoard( void );
	bool		isClient(std::string const &) const;

	bool		isPlayer(std::string const &) const;
	t_player*	findPlayer(std::string const &) const;
	void		createPlayer(std::string const &);
	void		deletePlayer(std::string const &);

	bool		isInDuel(t_player*) const;
	t_duel*		findDuel(t_player*) const;
	void		deleteDuel(t_duel*);

	Channel*				_myChannel;
	std::vector<t_duel*>	_pendingDuel;
	std::vector<t_player*>	_scoreBoard;
	
	std::string	_reply;
	
	
friend class Duel;
friend class Rank;
friend class Accept;
friend class Refuse;
friend class Scoreboard;
};

#endif
