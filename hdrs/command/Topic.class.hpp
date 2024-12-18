/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:37:15 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/18 19:46:00 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPIC_CLASS_HPP
# define TOPIC_CLASS_HPP
# include "ICommand.interface.hpp"
# include "Command.class.hpp"
# include <string>
# include <vector>

class Client;

class Topic : public ICommand {
	public:
		void	execute(Client const & client);

	private:
		Topic( void );
		~Topic( void );

		std::string const			_cmdName = "TOPIC";
		std::string&				_targetChannel;

		static Server* const	_server;
		
	friend Command;
};

#endif
