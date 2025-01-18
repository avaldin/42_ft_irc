#ifndef QUIT_CLASS_HPP
#	define QUIT_CLASS_HPP

#include "Client.class.hpp"
#include "ACommand.class.hpp"
#include "Server.class.hpp"

class Command;
class Server;

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

	friend class Command;

};

#endif
