/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 21:32:30 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/07 19:20:53 by tmouche          ###   ########.fr       */
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
		Client*		client;
		std::string error;
	}	t_data;

	void	checkRegistered(t_data& myData);
	void checkParams(t_data& myData);
	void	checkNicknameRestriction(t_data& myData);
	void	checkNicknameExist(t_data& myData);

	std::string const	_cmdName;
	std::string			_nickname;
	
	static Server*	_server;
	
	static void(Nick::*_method[4])(t_data&);

friend class Command;	
};

#endif
