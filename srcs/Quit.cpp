#include "Quit.class.hpp"
#include "Send.namespace.hpp"
#include "Exception.class.hpp"
#include "Error.define.hpp"

Server*	Quit::_server = Server::instantiate();

void	Quit::execute(Client &client) {
	t_data	myData;

	myData.message = this->_message;
	myData.client = &client;
	checkRegistered(myData);
	if (myData.error.empty()) {
		for (std::map<std::string, Channel *>::iterator it = _server->_serverChannel.begin(); it != _server->_serverChannel.end() ; ++it) {
			if (it->second->isClient(client._clientID)) {
				Send::ToChannel(*it->second, ":" + client._nickname + " QUIT :" + _message);
				it->second->deleteClient(client._clientID);
			}
		}
	}
	_server->eraseClient(client._clientID);
}


void Quit::checkRegistered(Quit::t_data &myData) {
	if (myData.client->status != REGISTERED)
		myData.error = ERR_NOTREGISTRATED(myData.client->_nickname);
}