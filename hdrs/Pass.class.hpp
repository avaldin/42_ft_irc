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
# include "ACommand.class.hpp"

class Client;
class Server;

class Pass : public ACommand {
public:
	void	execute(Client& client);

private:
	Pass( void );
	~Pass( void );

	typedef struct	s_data {
		std::string	error;
	}	t_data;
	
	std::string const	_cmdName;
	std::string			_password;

	static Server*	_server;
	
	static std::string(Pass::*_method[4])(t_data&);

friend class Command;	
};

#endif
