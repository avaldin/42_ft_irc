/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 23:17:06 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/29 23:18:17 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_CLASS_HPP
# define USER_CLASS_HPP
# include "ACommand.class.hpp"

class Client;
class Server;

class User : public ACommand {
public :
	void	execute(Client& client);
	
private:
	User( void ) {}
	~User( void ) {}
	
	typedef struct	s_data {
		Client*	client;
	}	t_data;

	std::string	checkRegistered(t_data& myData);
	std::string checkParams(t_data& myData);
	std::string	checkUsernameRestriction(t_data& myData);
	std::string	checkUsernameExist(t_data& myData);
	std::string checkNicknameExist(t_data& myData);

	std::string const	_cmdName;
	std::string			_Username;
	
	static Server*	_server;
	
	static std::string(User::*_method[5])(t_data&);

friend class Command;	
};



#endif
