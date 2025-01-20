/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:01:59 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/20 18:19:41 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITE_CLASS_HPP
# define INVITE_CLASS_HPP
# include "Command.class.hpp"
# include <string>
# include <vector>

class Client;
class Server;
class Channel;

class Invite : public Command {
	public:
		void	execute(Client& client);

		std::string const	cmdName;

	private:
		Invite( void ) : cmdName("INVITE") {}
		~Invite( void ) {}

		typedef struct s_data {
			std::string		targetUser;
			Client const *	targetClient;
			std::string		nameTargetChannel;
			Channel*		channel;
			std::string		error;
			Client const *	client;
		}	t_data;
	
		void	checkRegistered(t_data& myData);
		void	checkParams(t_data& myData);
		void	checkChannelExist(t_data& myData);
		void	checkChannelClient(t_data& myData);
		void	checkChannelOperator(t_data& myData);
		void	checkTargetExist(t_data& myData);
		void	checkChannelTarget(t_data& myData);
		
		std::vector<std::string>	_targetUsers;
		std::vector<std::string>	_targetChannels;
		
		static Server*	_server;
	
		static void(Invite::*_method[7])(t_data&);
	
	friend class Parser;
};

#endif
