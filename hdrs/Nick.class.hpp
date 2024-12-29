/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 21:32:30 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/30 00:13:29 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICK_CLASS_HPP
# define NICK_CLASS_HPP
# include "ACommand.class.hpp"

class Client;
class Server;

class Nick : public ACommand {
public :
	void	execute(Client& client);
	
private:
	Nick( void );
	~Nick( void );
	
	typedef struct	s_data {
		Client*	client;
	}	t_data;

	std::string	checkRegistered(t_data& myData);
	std::string checkParams(t_data& myData);
	std::string	checkNicknameRestriction(t_data& myData);
	std::string	checkNicknameExist(t_data& myData);
	std::string checkUsernameExist(t_data& myData);

	std::string const	_cmdName;
	std::string			_nickname;
	
	static Server*	_server;
	
	static std::string(Nick::*_method[5])(t_data&);

friend class Command;	
};

#endif
