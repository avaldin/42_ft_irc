/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.interface.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche < tmouche@student.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:29:24 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/21 00:58:02 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICOMMAND_INTERFACE_HPP
# define ICOMMAND_INTERFACE_HPP
# include <string>

class Command;
class Client;

class ICommand {
public:
	virtual ~ICommand( void ) {};
	virtual void	execute(Client const & client) = 0;
protected:
	std::string const	_cmdName;
};

#endif
