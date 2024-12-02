/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:03:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/02 15:38:47 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.class.hpp"
#include "Client.class.hpp"
#include "Error.define.hpp"

void	Server::pass(int clientId, const std::string& password)
{
	Client	*client = this->_clientDatabase[clientId];

	if (client->getRegistered())
		this->sendError(clientId, 462, ERR_ALREADYREGISTRED);
	else if (password.empty())
		this->sendError(clientId, 461, ERR_NEEDMOREPARAMS("PASS"));
	else if (password == this->getPassword())
		client->setRegistered(PASS);
	else
		this->sendError(clientId, 464, ERR_PASSWDMISMATCH);
}

//void	Server::nick(int clientId, const std::string& nickname)
//{
//	Client	*client = this->_clientDatabase[clientId];
//
//	for (std::map<int, Client *>::iterator it = this->_clientDatabase.begin() ; it != this->_clientDatabase.end() ; ++it)
//		if (it->second->getUsername() == nickname)
//			this->sendError(clientId, 433, ERR_NICKNAMEINUSE("wtf ?")); //bizarre ca
//	if (nickname.empty())
//		this->sendError(clientId, 461, ERR_NEEDMOREPARAMS(nickname));
//
//
//}
