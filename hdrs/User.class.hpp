/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:17:06 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/20 18:34:49 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_CLASS_HPP
# define USER_CLASS_HPP
# include "Command.class.hpp"
# define NB_CHECK 4

class Client;
class Server;

class User : public Command {
public :
	void	execute(Client& client);
	
	std::string const	cmdName;

private:
	User( void ) : cmdName("USER") {}
	~User( void ) {}
	
	typedef struct	s_data {
		Client*		client;
		std::string	error;
	}	t_data;

	void	checkRegistered(t_data& myData);
	void	checkParams(t_data& myData);
	void	checkUsernameRestriction(t_data& myData);
	void	checkModeExist(t_data& myData);

	std::string			_username;
	std::string			_mode;
	std::string			_realname;
	
	static Server*	_server;
	
	static void(User::*_method[4])(t_data&);

friend class Parser;	
};

#endif
