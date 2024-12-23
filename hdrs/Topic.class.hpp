/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:37:15 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/21 02:22:10 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPIC_CLASS_HPP
# define TOPIC_CLASS_HPP
# include "ICommand.interface.hpp"
# include <vector>

class Client;
class Channel;
class Server;

class Topic : public ICommand {
	public:
		void	execute(Client const & client);

	private:
		Topic( void );
		~Topic( void );
		
		typedef struct s_data {
			Channel* channel;
			Client	const *	client;
		}	t_data;
		
		std::string	checkChannelExist(t_data const & myData) const;
		std::string	checkCommandMessage(t_data const & myData) const;
		std::string	checkChannelClient(t_data const & myData) const;
		std::string	checkChannelOperator(t_data const & myData) const;

		std::string const			_cmdName;
		std::string					_targetChannel;
		std::string					_topic;

		static Server*	_server;

		static std::string(Topic::*_method[4])(t_data const &) const;
		
	friend class Command;
};

#endif
