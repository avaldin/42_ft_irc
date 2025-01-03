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

Server*	Pass::_server = Server::instantiate();

std::string(Pass::*Pass::_method[3])(t_data&) = {
	&Pass::checkRegistered,
	&Pass::checkParams, 
	&Pass::checkPassword};

Pass::Pass( void ) : _cmdName("PASS") {
	return ;
}

Pass::~Pass( void ) {
	return ;
}

void	Pass::execute(Client& client) {
	t_data		myData;
	std::string	error;

	myData.client = &client;
	for (int idx = 0; idx < 3 && !error.empty(); idx++)
		error = (this->*_method[idx])(myData);
	if (!error.empty()) {
		Send::ToClient(client._clientID, error);
		return ;
	}
	client.status = ONGOING_REGISTERING;
	return ;
}

std::string	Pass::checkRegistered(t_data& myData) {
	if (myData.client->status > NOT_REGISTERED)
		return ERR_ALREADYREGISTRED;
	return "";
}

std::string	Pass::checkParams(t_data& myData) {
	(void)myData;
	if (this->_password.empty())
		return ERR_NEEDMOREPARAMS(this->_cmdName);
	return "";
}

std::string	Pass::checkPassword(t_data& myData) {
	(void)myData;
	if (this->_password.compare(this->_server->_serverPassword))
		return ERR_PASSWDMISMATCH;
	return "";
}
