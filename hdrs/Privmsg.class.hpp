
#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP
# define CHECK_MSG 5

#include "ACommand.class.hpp"
#include "Server.class.hpp"

class Command;
class Server;

typedef enum e_type {
	CHANNEL,
	CLIENT,
}			t_type;

class Privmsg : public ACommand {
public:
	void	execute(Client &client);

private:
	Privmsg() :_cmdName("PRIVMSG") {}
	~Privmsg() {}

	typedef struct	s_data {
		Client*		client;
		Channel*	targetChannel;
		std::string	target;
		t_type		targetType;
		std::string	message;
		std::string	error;
	}				t_data;


	void checkRegistered(t_data &myData);
	void checkParams(t_data &myData);
	void checkTargetClientExist(t_data &myData);
	void checkTargetChannelExist(t_data &myData);
	void checkAuthorisation(t_data &myData);

	std::string	const			_cmdName;
	std::string					_receiver;
	std::string					_message;
	static Server*				_server;

	static void(Privmsg::*_method[CHECK_MSG])(t_data&);

	friend class Command;

};
#endif
