/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:15:18 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/02 19:35:28 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_CLASS_HPP
# define COMMAND_CLASS_HPP
# include <string>
# include <vector>

class Client;

class Command {
public:
	Command( void );
	~Command( void );
	Command(Command const & src);

	Command&	operator=(Command & const rhs);

	void	parseRawline(std::string rawline);

	std::string					getPrefix( void );
	std::string					getCommand( void );
	std::string					getMessage( void );
	std::vector<std::string>	getArgs( void );
	
private:
	std::string					_prefix;
	std::string					_command;
	std::vector<std::string>	_arguments;
	std::string					_message;
};

#endif
