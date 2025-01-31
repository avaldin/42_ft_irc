/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:29:24 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/20 18:41:02 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_CLASS_HPP
# define COMMAND_CLASS_HPP
# include <string>

class Parser;
class Client;
struct t_data;

class Command {
public:
	Command( void ) {}
	virtual ~Command( void ) {}
	
	// virtual void	execute(Client const &) {}
	virtual void	execute(Client &) {}
	
	std::string const	cmdName;
};

#endif
