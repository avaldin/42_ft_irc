/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:01:59 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/18 19:31:42 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITE_CLASS_HPP
# define INVITE_CLASS_HPP
# include "ICommand.interface.hpp"
# include "Invite.class.hpp"
# include <string>

class Client;
class Server;
class Channel;

typedef struct s_data {
	struct s_user const *	targetUser;
	int						targetID;
	Client*					targetClient;
	std::string&			nameTargetChannel;
	Channel*				currentChannel;
	std::string				error;
}	t_data;

class Invite : public ICommand {
	public:
		void	execute(Client const & client);
	
	private:
		Invite( void );
		~Invite( void );
	
		void		_myCommand(Client const & client);
		std::string	checkChannelExist(t_data& data, Client const & client);
		std::string	checkChannelClient(t_data& data, Client const & client);
		std::string	checkChannelOperator(t_data& data, Client const & client);
		std::string	checkTargetExist(t_data& data, Client const & client);
		std::string	checkChannelTarget(t_data& data, Client const & client);
		
		std::string const			_cmdName = "INVITE";
		std::vector<t_user*>		_targetUsers;
		std::vector<std::string&>	_targetChannels;
		
		static Server* const	_server;
	
		static std::string(Invite::*_method[5])(t_data&, Client const &);
	
	friend Command;
};

#endif
