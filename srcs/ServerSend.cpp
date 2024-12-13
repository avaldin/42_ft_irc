/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSend.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:39:52 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/13 16:41:28 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include "Server.class.hpp"

void	Server::sendToConsole(int clientID, std::string message) {
	std::string const	prefix = ":" + this->_serverClient[clientID]->_nickname + "!" + this->_serverClient[clientID]->_username + "@" + this->_serverName;
	std::string const	line = prefix + " " + message;

	send(this->_console->_clientID, line.c_str(), line.size(), 0); // pb ca marche pas j ai essaye d envoyer le this->_mySocket mais ca plante, la on est sur une valeur fix de 1, le std::cout marche bien mais jsp j aime pas
	return ;
}

void	Server::sendToServer(int clientID, std::string message) {
	std::string const	line = this->_serverClient[clientID]->_nickname + " " + message;

	for (std::map<int, Client *>::iterator it = this->_serverClient.begin(); it != this->_serverClient.end(); it++) {
		int otherClient = it->second->_clientID;
		send(otherClient, line.c_str(), line.size(), 0);
	}
	return ;
}

void	Server::sendToChannel(int clientID, std::string channelName, std::string message) {
	std::string const	line = this->_serverClient[clientID]->_nickname + " " + message;
	
	this->_serverChannel[channelName]->sendToChannel(message);
	return ;
}

void	Server::sendToClient(int clientID, int targetID, std::string message) {
	std::string const	line = this->_serverClient[clientID]->_nickname + " " + message;

	send(targetID, line.c_str(), line.size(), 0);
	return ;
}
