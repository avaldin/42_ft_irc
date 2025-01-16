/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:03:19 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/16 20:37:20 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_CLASS_HPP
# define MODE_CLASS_HPP
# include "ACommand.class.hpp"

# include <vector>
# define CHECK_MODE 6
# define NUM_MODE 5

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
		void	execute(Client& client);
	
	private:
		Mode( void ) : _cmdName("MODE") {}
		~Mode( void ){}
		
		typedef struct	s_data {
			Client const *	client;
			std::string		error;
			Channel * const	channel;
		}	t_data;
	
		void	tFlag(struct s_mode const * currentMode, Channel * const currentChannel, int const clientID);
		void	iFlag(struct s_mode const * currentMode, Channel * const currentChannel, int const clientID);
		void	lFlag(struct s_mode const * currentMode, Channel * const currentChannel, int const clientID);
		void	kFlag(struct s_mode const * currentMode, Channel * const currentChannel, int const clientID);
		void	oFlag(struct s_mode const * currentMode, Channel * const currentChannel, int const clientID);
		
		void	checkRegistered(t_data& myData);
		void	checkParams(t_data& myData);
		void	checkChannelExist(t_data& myData);
	
		std::string const		_cmdName;
		std::vector<t_mode*>	_mode;
		std::string				_targetChannel;
				
		static Server*	_server;

		static void(Mode::*_funcMode[NUM_MODE])(t_mode const *, Channel * const, int const);
		static void(Mode::*_method[CHECK_MODE])(t_data&);
	
	friend class Command;
};

#endif
