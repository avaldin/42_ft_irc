/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:15:18 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/20 18:19:30 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP
# include "Mode.class.hpp"
# include <string>
# include <vector>
# include <map>

class Command;

typedef struct s_user {
	std::string	targetUsername;
	std::string	targetNickname;
	std::string	targetServer;
}	t_user;

class Client;

class Parser {
public:
	~Parser( void );
	Parser(std::string const & rawLine);

	Command*	getCommand( void );

	std::string	_cmdName;

	
private:
	Parser( void );

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

	Command*							_command;
	std::string							_rawLine;
	std::string							_password;

	std::map<std::string,void(Parser::*)(std::vector<std::string>, int)>	_cmdMethods;
};

#endif
