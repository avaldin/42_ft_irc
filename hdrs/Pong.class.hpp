#ifndef PONG_CLASS_HPP
# define PONG_CLASS_HPP

#include "ACommand.class.hpp"
#include "Server.class.hpp"

class	Pong : public ACommand {
public:
	void	execute(Client &client);

private:
	Pong() : _cmdName("PONG") {}
	~Pong() {}

	std::string	_token;
	std::string	_cmdName;

	static Server*	_server;

friend class Command;

};



#endif