#ifndef PING_HPP
# define PING_HPP

# include "ACommand.class.hpp"
# include <vector>

class Ping : public ACommand {
public:
	void execute(Client const & client);

private:
	Ping(void) : _cmdName("PING") {}
	~Ping(void) {}

	typedef struct s_data {
		Client const	*client;
		std::string		token;
		std::string		error;
	}	t_data;

	void	checkRegistered(t_data& myData);
	void	checkParams(t_data &myData);

	std::string			_token;
	std::string const	_cmdName;

	static void (Ping::*_method[2])(t_data&);

friend class Command;
};

#endif