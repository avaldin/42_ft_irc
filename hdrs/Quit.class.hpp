#ifndef QUIT_CLASS_HPP
#	define QUIT_CLASS_HPP

#include "Client.class.hpp"
#include "ACommand.class.hpp"
#include "Server.class.hpp"

class Command;
class Server;

typedef enum e_type {
	CHANNEL,
	CLIENT,
}			t_type;

class Quit : public ACommand {
public:
	void	execute(Client &client);

private:
	Quit() :_cmdName("Quit") {}
	~Quit() {}

	typedef struct	s_data {
		std::string	message;
		Client*		client;
		std::string	error;
	}				t_data;


	void checkRegistered(t_data &myData);

	std::string	const			_cmdName;
	std::string					_message;
	static Server*				_server;

	static void(Quit::*_method[3])(t_data&);

	friend class Command;

};

#endif
