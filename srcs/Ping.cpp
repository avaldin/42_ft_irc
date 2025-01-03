#include "Ping.class.hpp"
#include "Error.define.hpp"
#include "Client.class.hpp"
#include "Send.namespace.hpp"

void(Ping::*Ping::_method[2])(t_data&) = {
		&Ping::checkParams,
		&Ping::checkRegistered,
};

void	Ping::checkRegistered(t_data& myData) {
	if (myData.client->status != REGISTERED)
		myData.error = ERR_NOTREGISTRATED;
}

void	Ping::checkParams(t_data& myData) {
	if (myData.token.empty())
		myData.error =  ERR_NEEDMOREPARAMS(this->_cmdName);
}

void	Ping::execute(Client const & client) {
	t_data		myData;
	std::string	error;

	myData.client = &client;
	myData.token = this->_token;
	for (int idx = 0; idx < 2 && !error.empty(); idx++)
		(this->*_method[idx])(myData);
	if (!error.empty()) {
		Send::ToClient(client._clientID, error);
		return ;
	}
	Send::ToClient(client._clientID, "PONG :" + myData.token);
}