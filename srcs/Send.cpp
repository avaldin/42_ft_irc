/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Send.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:58:06 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/17 17:59:46 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Send.namespace.hpp"
#include "Channel.class.hpp"
#include "Client.class.hpp"
#include <sys/socket.h>


void	Send::ToConsole(int const & targetID, std::string const & message) {
	send(targetID, message.c_str(), message.size(), 0);
	return ;
}

void	Send::ToServer(std::map<int, Client*> & serverClient, std::string const & message) {
	for (std::map<int, Client *>::iterator it = serverClient.begin(); it != serverClient.end(); it++) {
		int otherClient = it->second->_clientID;
		send(otherClient, message.c_str(), message.size(), 0);
	}
	return ;
}

void	Send::ToChannel(Channel const & channel, std::string const & message) {
	channel.sendToChannel(message);
	return ;
}

void	Send::ToClient(int const & targetID, std::string const & message) {
	send(targetID, message.c_str(), message.size(), 0);
	return ;
}
