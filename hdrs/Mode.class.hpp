/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:03:19 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/30 18:24:49 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_CLASS_HPP
# define MODE_CLASS_HPP
# include "ACommand.class.hpp"

# include <vector>

class Command;
class Client;
class Channel;
class Server;

typedef struct s_mode {
	unsigned int				sign;
	char						mode;
	std::string					args;
}	t_mode;

class Mode : public ACommand {
	public:
		void	execute(Client const & client);
	
	private:
		Mode( void ) : _cmdName("MODE") {}
		~Mode( void ){}
		
		typedef struct	s_data {
			Client const *	client;
		}	t_data;
	
		void	tFlag(struct s_mode const * currentMode, Channel * const currentChannel, int const clientID);
		void	iFlag(struct s_mode const * currentMode, Channel * const currentChannel, int const clientID);
		void	lFlag(struct s_mode const * currentMode, Channel * const currentChannel, int const clientID);
		void	kFlag(struct s_mode const * currentMode, Channel * const currentChannel, int const clientID);
		void	oFlag(struct s_mode const * currentMode, Channel * const currentChannel, int const clientID);
		
		std::string	checkRegistered(t_data& myData);
		std::string	checkParams(t_data& myData);
	
		std::string const			_cmdName;
		std::vector<t_mode*>		_mode;
		std::vector<std::string>	_targetChannels;

		static Server*	_server;
	
	friend class Command;
};

#endif
