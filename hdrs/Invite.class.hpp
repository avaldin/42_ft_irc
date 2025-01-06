/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:01:59 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/19 18:44:06 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITE_CLASS_HPP
# define INVITE_CLASS_HPP
# include "ICommand.interface.hpp"
# include <string>
# include <vector>

class Client;
class Server;
class Channel;

class Invite : public ICommand {
	public:
		void	execute(Client const & client);
	
	private:
		Invite( void );
		~Invite( void );

		typedef struct s_data {
			t_user const *			targetUser;
			int						targetID;
			Client const *			targetClient;
			std::string				nameTargetChannel;
			Channel*				channel;
			std::string				error;
			Client const *			client;
		}	t_data;
	
		std::string	checkChannelExist(t_data& myData);
		std::string	checkChannelClient(t_data& myData);
		std::string	checkChannelOperator(t_data& myData);
		std::string	checkTargetExist(t_data& myData);
		std::string	checkChannelTarget(t_data& myData);
		
		std::string const			_cmdName;
		std::vector<t_user*>		_targetUsers;
		std::vector<std::string>	_targetChannels;
		
		static Server*	_server;
	
		static std::string(Invite::*_method[5])(t_data&);
	
	friend class Command;
};

#endif
