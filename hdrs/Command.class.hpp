/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:15:18 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/04 17:24:48 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_CLASS_HPP
# define COMMAND_CLASS_HPP
# include <string>
# include <vector>
# include <map>

typedef struct s_user {
	std::string	targetUsername;
	std::string	targetNickname;
	std::string	targetServer;
}	t_user;

class Client;

class Command {
public:
	~Command( void );
	Command(std::string const & rawLine);

	std::string					getPrefix( void );
	std::string					getCommand( void );
	std::string					getPassword( void );
	std::string					getMessage( void );
	std::vector<std::string>	getTargetChannels( void );
	std::vector<t_user*>		getTargetUsers( void );
	
	bool						onError;
	std::string					err;
	bool						onReply;
	std::string					rpl;
private:
	Command( void );
	Command(Command const & src);
	Command&	operator=(Command & const rhs);

	void	parseRawline(std::string rawline);
	t_user*	parseUser(std::string user);
	
	void	setPASS(std::vector<std::string> splitedLine, int idx);
	void	setNICK(std::vector<std::string> splitedLine, int idx);
	void	setUSER(std::vector<std::string> splitedLine, int idx);
	void	setJOIN(std::vector<std::string> splitedLine, int idx);
	void	setKICK(std::vector<std::string> splitedLine, int idx);
	void	setTOPIC(std::vector<std::string> splitedLine, int idx);
	void	setMODE(std::vector<std::string> splitedLine, int idx);
	void	setINVITE(std::vector<std::string> splitedLine, int idx);
	void	setQUIT(std::vector<std::string> splitedLine, int idx);

	std::string					_rawLine;

	std::string					_prefix;
	std::string					_command;
	std::string					_password;
	std::string					_message;
	std::vector<std::string>	_targetChannels;
	std::vector<t_user*>		_targetUsers;
	
	std::map<std::string,void(Command::*)(std::vector<std::string> splitedLine, int idx)>	_cmdMethods;
};

#endif
