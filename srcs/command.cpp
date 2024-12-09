/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:03:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/09 13:07:05 by avaldin          ###   ########.fr       */
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

static bool	invalidNickname(std::string	nickname)
{

	for (unsigned long i = 0; i < nickname.length(); ++i)
	{
		if (isdigit(nickname[0]))
			return (true);
		if (!isalnum(nickname[i]) && nickname[i] != '[' && nickname[i] != ']'
			&& nickname[i] != '{' && nickname[i] != '}' && nickname[i] != '\\'
			&& nickname[i] != '|')
			return (false);
	}
	return (true);
}

void	Server::nick(int clientId, const std::string& nickname)
{
	Client *client = this->_clientDatabase[clientId];
	if (client->getRegistered() == NOT_REGISTERED)
		this->sendError(clientId, 451, ERR_NOTREGISTRATED);
	if (nickname.empty())
	{
		this->sendError(clientId, 461, ERR_NEEDMOREPARAMS("wtf"));
		return ;
	}
	if (invalidNickname(nickname))
	{
		this->sendError(clientId, 433, ERR_NICKNAMEINUSE("wtf ?")); //bizarre ca
		return ;
	}
	for (std::map<int, Client *>::iterator it = this->_clientDatabase.begin() ; it != this->_clientDatabase.end() ; ++it)
		if (it->second->getUsername() == nickname)
		{
			this->sendError(clientId, 433, ERR_NICKNAMEINUSE("wtf ?")); //bizarre ca
			return ;
		}
	client->setNickname(nickname);
	if (client->getRegistered() == PASS)
		client->setRegistered(NICK);
	else
		client->setRegistered(REGISTERED);
}

void	Server::user(int clientId, const std::string& username)
{
	Client *client = this->_clientDatabase[clientId];
	if (client->getRegistered() == NOT_REGISTERED)
		this->sendError(clientId, 451, ERR_NOTREGISTRATED);


	client->setNickname(username);
	client->setRegistered(REGISTERED);
	if (client->getRegistered() == PASS)
		client->setRegistered(USER);
}