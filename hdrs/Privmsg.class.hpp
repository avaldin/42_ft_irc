
#ifndef PRIVMSG_CLASS_HPP
# define PRIVMSG_CLASS_HPP

#include "ACommand.class.hpp"
#include "Server.class.hpp"

class	Privmsg : public ACommand {
public:
	void	execute(Client &client);

private:
	Privmsg( void ) :_cmdName("PRIVMSG") {}
	~Privmsg( void ) {}

	typedef struct	s_data {
		Client*		client;
		std::string	error;
	}				t_data;


	void checkRegistered(t_data &myData);
	void checkParams(t_data &myData);

	std::string	const			_cmdName;

	static Server*	_server;

	static void(Privmsg::*_method[2])(t_data&);
};
#endif
