#include <sstream>
#include "Pong.class.hpp"
#include "Server.class.hpp"

Server*	Pong::_server = Server::instantiate();

void Pong::execute(Client &client)
{
	unsigned int		newPing;
	std::stringstream	ss(this->_token);

	ss >> newPing;
	if (ss.fail())
		return ;
	if (newPing == _server->_lastPing)
	{
		for (std::list<int>::iterator it = _server->_idPing.begin(); it != _server->_idPing.end(); it++)
			if (*it == client._clientID)
			{
				_server->_idPing.erase(it);
				return ;
			}
	}
}
