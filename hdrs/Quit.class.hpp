/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:21:25 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/20 18:33:17 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUIT_CLASS_HPP
#	define QUIT_CLASS_HPP

#include "Client.class.hpp"
#include "Command.class.hpp"
#include "Server.class.hpp"

class Parser;
class Server;

class Quit : public Command {
public:
	void	execute(Client &client);

private:
	Quit() : _cmdName("QUIT") {}
	~Quit() {}

	typedef struct	s_data {
		std::string	message;
		Client*		client;
		std::string	error;
	}				t_data;


	void checkRegistered(t_data &myData);

	std::string	const			_cmdName;
	std::string					_message;
	static Server*				_server;

	friend class Parser;

};

#endif
