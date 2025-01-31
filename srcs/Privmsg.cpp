#include "Privmsg.class.hpp"
#include "Server.class.hpp"
#include "Send.namespace.hpp"
#include "Error.define.hpp"

Server*	Privmsg::_server = Server::instantiate();

void(Privmsg::*Privmsg::_method[CHECK_MSG])(t_data&) = {
		&Privmsg::checkRegistered,
		&Privmsg::checkParams,
		&Privmsg::checkTargetClientExist,
		&Privmsg::checkTargetChannelExist,
		&Privmsg::checkAuthorisation
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
	for (int idx = 0; idx < CHECK_MSG && myData.error.empty(); ++idx)
		(this->*_method[idx])(myData);
	if (!myData.error.empty()) {
		Send::ToClient(client._clientID, myData.error);
		return ;
	}
	std::string	toSend(":" + client._nickname + " PRIVMSG " + myData.target + " :" + _message);
	if (myData.targetType == CLIENT)
		Send::ToClient(this->_server->findClientNickname(_receiver)->_clientID, toSend);
	else if (myData.targetType == CHANNEL) {
		myData.targetChannel->privMsgToChannel(toSend, client._clientID);
		if (this->_message.size()) {
			std::string	botAnswer( myData.targetChannel->_myBot.useBot(client, this->_message, *myData.targetChannel));
			if (!botAnswer.empty())
				Send::ToChannel(*myData.targetChannel, ":Duelbot PRIVMSG " + myData.target + " :" + botAnswer);
		}
	}
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

void	Privmsg::checkTargetClientExist(t_data& myData) {
	if (myData.targetType == CLIENT && !this->_server->findClientNickname(myData.target))
		myData.error = ERR_NOSUCHNICK(myData.client->_nickname, myData.target);
}

void	Privmsg::checkTargetChannelExist(t_data& myData) {
	std::map<std::string,Channel*>::iterator	it = this->_server->_serverChannel.find(myData.target);

	if (myData.targetType == CHANNEL && it == this->_server->_serverChannel.end())
		myData.error = ERR_NOSUCHCHANNEL(myData.client->_nickname, myData.target);
	else if (myData.targetType == CHANNEL)
		myData.targetChannel = it->second;
}

void	Privmsg::checkAuthorisation(t_data& myData) {
	if (myData.targetType == CHANNEL && !myData.targetChannel->isClient(myData.client->_clientID))
		myData.error = ERR_CANNOTSENDTOCHAN(myData.client->_nickname, myData.target);
}