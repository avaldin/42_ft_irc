/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:03:19 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/19 18:44:26 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_CLASS_HPP
# define MODE_CLASS_HPP
# include "ICommand.interface.hpp"

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

class Mode : public ICommand {
	public:
		void	execute(Client const & client);
	
	private:
		Mode( void );
		~Mode( void );
	
		void	tFlag(struct s_mode const * currentMode, Channel * const currentChannel, int const clientID);
		void	iFlag(struct s_mode const * currentMode, Channel * const currentChannel, int const clientID);
		void	lFlag(struct s_mode const * currentMode, Channel * const currentChannel, int const clientID);
		void	kFlag(struct s_mode const * currentMode, Channel * const currentChannel, int const clientID);
		void	oFlag(struct s_mode const * currentMode, Channel * const currentChannel, int const clientID);
		
		std::string const			_cmdName;
		std::vector<t_mode*>		_mode;
		std::vector<std::string>	_targetChannels;

		static Server*	_server;
	
	friend class Command;
};

#endif
