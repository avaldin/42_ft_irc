/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSend.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:39:52 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/16 19:50:20 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include "Server.class.hpp"

Server::Send::Send( void ) {
	return ;
}


void	Server::Send::ToConsole(int const targetID, std::string const message) {
	send(targetID, message.c_str(), message.size(), 0); // pb ca marche pas j ai essaye d envoyer le this->_mySocket mais ca plante, la on est sur une valeur fix de 1, le std::cout marche bien mais jsp j aime pas
	return ;
}

void	Server::Send::ToServer(std::string const message) {
	for (std::map<int, Client *>::iterator it = this->_serverClient.begin(); it != this->_serverClient.end(); it++) {
		int otherClient = it->second->_clientID;
		send(otherClient, message.c_str(), message.size(), 0);
	}
	return ;
}

void	Server::Send::ToChannel(int const targetID, std::string const channelName, std::string const message) {
	this->_serverChannel[channelName]->sendToChannel(message);
	return ;
}

void	Server::Send::ToClient(int const targetID, std::string const message) {
	send(targetID, message.c_str(), message.size(), 0);
	return ;
}
