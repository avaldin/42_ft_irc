#include "Quit.class.hpp"
#include "Send.namespace.hpp"
#include "Exception.class.hpp"

Server*	Quit::_server = Server::instantiate();

void	Quit::execute(Client &client) {
	t_data	myData;

	myData.message = this->_message;
	myData.client = &client;
	checkRegistered(myData);
	if (!myData.error.empty()) {
		Send::ToClient(client._clientID, myData.error);
		return ;
	}
	for (std::map<std::string, Channel *>::iterator it = _server->_serverChannel.begin(); it != _server->_serverChannel.end() ; ++it) {
		if (it->second->isOperator(client._clientID))
			it->second->deleteOperator(client._clientID);
		if (it->second->isClient(client._clientID)) {
			Send::ToChannel(*it->second, ":" + client._nickname + " QUIT :" + _message);
			it->second->deleteClient(client._clientID);
		}
	}
	if (epoll_ctl(_server->_epollfd, EPOLL_CTL_DEL, client._clientID, nullptr) == -1)
		throw EpollCtlException();
	_server->eraseClient(client._clientID)
}


void checkRegistered(t_data &myData) {
	if ()
}