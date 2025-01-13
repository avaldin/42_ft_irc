/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:37:15 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/13 18:41:27 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPIC_CLASS_HPP
# define TOPIC_CLASS_HPP
# include "ACommand.class.hpp"
# include <vector>
# define CHECK_TOPIC 6

class Client;
class Channel;
class Server;

class Topic : public ACommand {
	public:
		void	execute(Client& client);

	private:
		Topic( void );
		~Topic( void );
		
		typedef struct s_data {
			std::string		error;
			Channel* 		channel;
			Client	const *	client;
		}	t_data;
		
		void	checkRegistered(t_data& myData);
		void	checkParams(t_data& myData);
		void	checkChannelExist(t_data& myData);
		void	checkCommandMessage(t_data& myData);
		void	checkChannelClient(t_data& myData);
		void	checkChannelOperator(t_data& myData);

		std::string const	_cmdName;
		std::string			_targetChannel;
		std::string			_topic;

		static Server*	_server;

		static void(Topic::*_method[CHECK_TOPIC])(t_data&);
		
	friend class Command;
};

#endif
