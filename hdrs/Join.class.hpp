/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:59:40 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/02 17:25:11 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_CLASS_HPP
# define JOIN_CLASS_HPP
# include "ACommand.class.hpp"
# include <vector>
# define NB_CHECK 2

class Client;
class Server;

class Join : public ACommand {
public :
	void	execute(Client& client);
	
private:
	Join( void ) : _cmdName("JOIN") {}
	~Join( void ) {}
	
	typedef struct	s_data {
		Client*		client;
		Channel*	targetChannel;
		std::string	error;
	}	t_data;

	void	checkRegistered(t_data& myData);
	void	checkParams(t_data& myData);

	std::string const			_cmdName;
	std::vector<std::string>	_targetChannels;
	std::vector<std::string>	_targetKeys;

	static Server*	_server;
	
	static void(Join::*_method[NB_CHECK])(t_data&);

friend class Command;	
};

#endif
