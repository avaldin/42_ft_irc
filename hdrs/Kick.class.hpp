/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 00:04:44 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/26 18:41:30 by tmouche          ###   ########.fr       */
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
	Kick( void );
	~Kick( void );

	typedef struct	s_data {
		Channel*		channel;
		Client const *	client;
		int				idxChannel;
		int				idxUser;
		struct s_user*	targetUser;
		int				targetID;
		Client*			targetClient;
	}	t_data;
	
	std::string	checkRegistered(t_data& myData);
	std::string	checkParams(t_data& myData);
	std::string	checkChannelExist(t_data& myData);
	std::string checkClientTargetExist(t_data& myData);
	std::string checkChannelClient(t_data& myData);
	std::string	checkChannelOperator(t_data& myData);
	
	std::string const				_cmdName;
	std::string						_message;
	std::vector<struct s_user*>		_targetUsers;
	std::vector<std::string>		_targetChannels;
	
	static Server*	_server;

	static std::string(Kick::*_method[6])(t_data&);

	
friend class Command;
};
	
#endif
