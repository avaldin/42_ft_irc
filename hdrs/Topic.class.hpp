/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:37:15 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/26 19:24:06 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPIC_CLASS_HPP
# define TOPIC_CLASS_HPP
# include "ACommand.class.hpp"
# include <vector>

class Client;
class Channel;
class Server;

class Topic : public ACommand {
	public:
		void	execute(Client const & client);

	private:
		Topic( void );
		~Topic( void );
		
		typedef struct s_data {
			Channel* channel;
			Client	const *	client;
		}	t_data;
		
		std::string	checkRegistered(t_data& myData);
		std::string	checkParams(t_data& myData);
		std::string	checkChannelExist(t_data& myData);
		std::string	checkCommandMessage(t_data& myData);
		std::string	checkChannelClient(t_data& myData);
		std::string	checkChannelOperator(t_data& myData);

		std::string const			_cmdName;
		std::string					_targetChannel;
		std::string					_topic;

		static Server*	_server;

		static std::string(Topic::*_method[6])(t_data&);
		
	friend class Command;
};

#endif
