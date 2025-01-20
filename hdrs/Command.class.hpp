/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:15:18 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/20 15:59:43 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_CLASS_HPP
# define COMMAND_CLASS_HPP
# include "Mode.class.hpp"
# include <string>
# include <vector>
# include <map>

class ACommand;

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

	ACommand*					getCommand( void );
	
private:
	Command( void );
	Command(Command const & src);
	Command&	operator=(Command const & rhs);

	void	parseRawline( void );
	void	deleteNewline(std::string& line);
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
	void	setPRIVMSG(std::vector<std::string> splitedLine, int idx);

	ACommand*							_command;
	std::string							_rawLine;
	std::string							_password;
	std::string							_cmdName;

	std::map<std::string,void(Command::*)(std::vector<std::string>, int)>	_cmdMethods;
};

#endif
