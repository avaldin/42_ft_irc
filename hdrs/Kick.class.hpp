/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 00:04:44 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/30 17:52:59 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICK_CLASS_HPP
# define KICK_CLASS_HPP
# include "ACommand.class.hpp"
# include <vector>

class Client;
class Channel;
class Client;
class Server;

class Kick : public ACommand {
public:
	void	execute(Client const & client);

private:
	Kick( void ) : _cmdName("KICK") {}
	~Kick( void ) {}

	typedef struct	s_data {
		Channel*		channel;
		Client const *	client;
		int				idxChannel;
		int				idxUser;
		struct s_user*	targetUser;
		Client*			targetClient;
		std::string		error;
	}	t_data;
	
	void	checkRegistered(t_data& myData);
	void	checkParams(t_data& myData);
	void	checkChannelExist(t_data& myData);
	void	checkClientTargetExist(t_data& myData);
	void	checkChannelClient(t_data& myData);
	void	checkChannelOperator(t_data& myData);
	
	std::string const				_cmdName;
	std::string						_message;
	std::vector<struct s_user*>		_targetUsers;
	std::vector<std::string>		_targetChannels;
	
	static Server*	_server;

	static void(Kick::*_method[6])(t_data&);

	
friend class Command;
};
	
#endif
