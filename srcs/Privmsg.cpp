#include <iostream>
#include "Privmsg.class.hpp"
#include "Server.class.hpp"
#include "Send.namespace.hpp"
#include "Error.define.hpp"

Server*	Privmsg::_server = Server::instantiate();

void(Privmsg::*Privmsg::_method[3])(t_data&) = {
		&Privmsg::checkRegistered,
		&Privmsg::checkParams,
		&Privmsg::checkTargetExist
		};

void	Privmsg::execute(Client &client) {
	t_data		myData;

	myData.client = &client;
	myData.target = _receiver;
	myData.message = _message;
	if (this->_receiver.find_first_of("#&+!") == 0)
		myData.targetType = CHANNEL;
	else
		myData.targetType = CLIENT;
	for (int idx = 0; idx < 3 && myData.error.empty(); ++idx)
		(this->*_method[idx])(myData);
	std::cout << "err ->" << myData.error << std::endl;
	if (!myData.error.empty()) {
		Send::ToClient(client._clientID, myData.error);
		return ;
	}
	std::string	toSend(":" + client._nickname + " PRIVMSG " + myData.target + " :" + _message);
	if (myData.targetType == CLIENT)
		Send::ToClient(this->_server->findClientNickname(_receiver)->_clientID, toSend);
	else if (myData.targetType == CHANNEL)
		this->_server->_serverChannel[myData.target]->privMsgToChannel(_message, client._clientID);
}

void	Privmsg::checkRegistered(t_data& myData) {
	if (myData.client->status < REGISTERED)
		myData.error = ERR_NOTREGISTRATED(myData.client->_nickname);
}

void	Privmsg::checkParams(t_data& myData) {
	if (myData.target.empty())
		myData.error = ERR_NORECIPIENT(myData.client->_nickname, "PRIVMSG");
	else if (myData.message.empty())
		myData.error = ERR_NOTEXTTOSEND(myData.client->_nickname);
}

void	Privmsg::checkTargetExist(t_data& myData) {
	if (myData.targetType == CLIENT && !this->_server->findClientNickname(myData.target))
		myData.error = ERR_NOSUCHNICK(myData.client->_nickname, myData.target);
	if (myData.targetType == CHANNEL
			&& this->_server->_serverChannel.find(myData.target) == this->_server->_serverChannel.end())
		myData.error = ERR_NOSUCHCHANNEL(myData.client->_nickname, myData.target);
}