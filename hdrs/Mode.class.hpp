/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:03:19 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/22 12:27:15 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_CLASS_HPP
# define MODE_CLASS_HPP
# include "Command.class.hpp"

# include <vector>
# define CHECK_MODE 6
# define NUM_MODE 6
# define LOWEST_MODE 105

class Parser;
class Client;
class Channel;
class Server;

typedef struct s_mode {
	unsigned int				sign;
	char						mode;
	std::string					args;
}	t_mode;

class Mode : public Command {
	public:
		void	execute(Client& client);

		std::string const	cmdName;
	
	private:
		Mode( void ) : cmdName("MODE") {}
		~Mode( void );
		
		typedef struct	s_data {
			Client const *	client;
			Client const *	target;
			Channel*		channel;
			t_mode*			mode;
			int				idxCheck;
			std::string		error;
		}	t_data;
	
		void	tFlag(struct s_mode const * currentMode, t_data& myData);
		void	iFlag(struct s_mode const * currentMode, t_data& myData);
		void	lFlag(struct s_mode const * currentMode, t_data& myData);
		void	kFlag(struct s_mode const * currentMode, t_data& myData);
		void	oFlag(struct s_mode const * currentMode, t_data& myData);
		void	unknownFlag(struct s_mode const * currentMode, t_data& myData);
		
		void	checkRegistered(t_data& myData);
		void	checkParams(t_data& myData);
		void	checkChannelExist(t_data& myData);
		void	checkChannelOperator(t_data& myData);
		void	checkClientTarget(t_data& myData);

		std::string 	modeString(Channel& channel);

		unsigned int	idxFuncMode(unsigned int const mode);
	
		std::vector<t_mode*>	_mode;
		std::string				_targetChannel;
				
		static Server*	_server;

		static void(Mode::*_funcMode[NUM_MODE])(t_mode const *, t_data& myData);
		static void(Mode::*_method[CHECK_MODE])(t_data&);
	
	friend class Parser;
};

#endif
