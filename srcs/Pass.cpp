/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:20:39 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/26 15:21:31 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.class.hpp"
#include "Error.define.hpp"
#include "Server.class.hpp"
#include "Send.namespace.hpp"

#include "Client.class.hpp"

#include <iostream>

Server*	Pass::_server = Server::instantiate();

void(Pass::*Pass::_method[3])(t_data&) = {
	&Pass::checkRegistered,
	&Pass::checkParams, 
	&Pass::checkPassword};

void	Pass::execute(Client& client) {
	t_data		myData;

	myData.client = &client;
	myData.password = this->_password;
	for (int idx = 0; idx < 3 && myData.error.empty(); idx++)
		(this->*_method[idx])(myData);
	if (!myData.error.empty()) {
		Send::ToClient(client._clientID, myData.error);
		return ;
	}
	std::cout << "pass status" << std::endl;
	client.status = ONGOING_REGISTERING;
	return ;
}

void	Pass::checkRegistered(t_data& myData) {
	if (myData.client->status > NOT_REGISTERED)
		myData.error = ERR_ALREADYREGISTRED;
}

void	Pass::checkParams(t_data& myData) {
	if (this->_password.empty())
		myData.error = ERR_NEEDMOREPARAMS(this->_cmdName);
}

void	Pass::checkPassword(t_data& myData) {
	if (myData.password.compare(this->_server->_serverPassword))
		myData.error = ERR_PASSWDMISMATCH;
}
