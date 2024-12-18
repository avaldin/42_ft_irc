/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.interface.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:29:24 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/18 19:31:17 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICOMMAND_INTERFACE_HPP
# define ICOMMAND_INTERFACE_HPP
# include <string>

class Command;

class ICommand {
public:
	virtual ~ICommand( void ) {};
	virtual void	execute(Client const & client) = 0;
private:
	std::string	_cmdName = 0;
};

#endif
