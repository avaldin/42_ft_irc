/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:15:18 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/03 20:14:04 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_CLASS_HPP
# define COMMAND_CLASS_HPP
# include <string>
# include <vector>

typedef struct s_user {
	std::string	targetUsername;
	std::string	targetNickname;
	std::string	targetServer;
}	t_user;

class Client;

class Command {
public:
	Command( void );
	~Command( void );
	Command(Command const & src);
	Command(std::string const & rawLine);

	Command&	operator=(Command & const rhs);

	void	parseRawline(std::string rawline);

	std::string					getPrefix( void );
	std::string					getCommand( void );
	std::string					getMessage( void );
	std::vector<std::string>	getArgs( void );
	
private:
	std::string					_rawLine;

	std::string					_prefix;
	std::string					_command;
	std::string					_password;
	std::string					_targetChannel;
	std::vector<std::string>	_targetChannels;
	std::vector<t_user*>		_targetUsers;
	
};

#endif
