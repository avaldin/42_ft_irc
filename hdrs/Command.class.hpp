/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:15:18 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/03 23:03:41 by thibaud          ###   ########.fr       */
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
	Command(Command const & src);


	void	parseRawline(std::string rawline);
	
	void	setPASS(std::vector<std::string> splitedLine, int idx);
	void	setNICK(std::vector<std::string> splitedLine, int idx);
	void	setUSER(std::vector<std::string> splitedLine, int idx);
	void	setJOIN(std::vector<std::string> splitedLine, int idx);
	void	setKICK(std::vector<std::string> splitedLine, int idx);
	void	setTOPIC(std::vector<std::string> splitedLine, int idx);
	void	setMODE(std::vector<std::string> splitedLine, int idx);
	void	setINVITE(std::vector<std::string> splitedLine, int idx);
	void	setQUIT(std::vector<std::string> splitedLine, int idx);

private:
	Command( void );
	Command(std::string const & rawLine);
	Command&	operator=(Command & const rhs);

	std::string					_rawLine;

	std::string					_prefix;
	std::string					_command;
	std::string					_password;
	std::string					_targetChannel;
	std::vector<std::string>	_targetChannels;
	std::vector<t_user*>		_targetUsers;
	
	std::map<std::string,void(Command::*)(std::vector<std::string> splitedLine, int idx)>	_cmdMethods;
};

#endif
