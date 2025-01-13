/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:13:28 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/26 15:26:30 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Pass_CLASS_HPP
# define Pass_CLASS_HPP

#include <iostream>
# include "ACommand.class.hpp"

class Client;
class Server;

class Pass : public ACommand {
public:
	void	execute(Client& client);

private:
	Pass( void ) : _cmdName("PASS") {}
	~Pass( void ) {}

	typedef struct	s_data {
		Client*		client;
		std::string	error;
		std::string	password;
	}	t_data;

	void	checkRegistered(t_data& myData);
	void	checkParams(t_data& myData);
	void	checkPassword(t_data& myData);
	
	std::string const	_cmdName;
	std::string			_password;

	static Server*	_server;
	
	static void(Pass::*_method[3])(t_data&);

friend class Command;	
};

#endif
