#include "Privmsg.class.hpp"
#include "Server.class.hpp"
#include "Send.namespace.hpp"
#include "Error.define.hpp"

Server*	Privmsg::_server = Server::instantiate();

void(Privmsg::*Privmsg::_method[2])(t_data&) = {
		&Privmsg::checkRegistered,
		&Privmsg::checkParams,
		};

void	Privmsg::execute(Client &client) {
	t_data		myData;
	std::string	error;

//	myData.client = &client;
	for (int idx = 0; idx < 3 && !error.empty(); idx++)
		(this->*_method[idx])(myData);
	if (!error.empty()) {
		Send::ToClient(client._clientID, error);
		return ;
	}
	return ;
}

void	Privmsg::checkRegistered(t_data& myData) {
	if (myData.client->status > NOT_REGISTERED)
		myData.error = ERR_ALREADYREGISTRED;
}

void	Privmsg::checkParams(t_data& myData) {
	if (myData.client->status > NOT_REGISTERED)
		myData.error = ERR_ALREADYREGISTRED;
}
