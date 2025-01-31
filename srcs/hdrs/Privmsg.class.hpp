
#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP
# define CHECK_MSG 5

#include "Command.class.hpp"
#include "Server.class.hpp"

class Parser;
class Server;

typedef enum e_type {
	CHANNEL,
	CLIENT,
}			t_type;

class Privmsg : public Command {
public:
	void	execute(Client &client);

	std::string	const	cmdName;

private:
	Privmsg() : cmdName("PRIVMSG") {}
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

	std::string					_receiver;
	std::string					_message;
	static Server*				_server;

	static void(Privmsg::*_method[CHECK_MSG])(t_data&);

	friend class Parser;

};
#endif
