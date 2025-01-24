/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandBot.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 03:40:46 by thibaud           #+#    #+#             */
/*   Updated: 2025/01/24 06:16:35 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDBOT_CLASS_HPP
# define COMMANDBOT_CLASS_HPP
# include <string>

class Client;
class Channel;

class CommandBot {
public:
	CommandBot( void ) {}
	virtual ~CommandBot( void ) {}
	
	virtual std::string	execute(Client&, Channel&) {return "";}
	
	std::string const	cmdName;
};

#endif