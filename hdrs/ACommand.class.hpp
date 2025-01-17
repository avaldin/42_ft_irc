/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:29:24 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/13 18:38:19 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACOMMAND_CLASS_HPP
# define ACOMMAND_CLASS_HPP
# include <string>

class Command;
class Client;
struct t_data;

class ACommand {
public:
	ACommand ( void ) {};
	virtual ~ACommand( void ) {};
	
	virtual void	execute(Client const &) {};
	virtual void	execute(Client &) {};

// private:
// 	virtual std::string	checkRegistered(t_data& myData) {}
// 	virtual std::string checkParams(t_data& myData) {}
};

#endif
