/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:43:48 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/04 17:23:40 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CLASS_HPP
# define SERVER_CLASS_HPP
# define nullptr 0

#include "Client.class.hpp"
#include "Channel.class.hpp"

# include <map>
# include <string>
# include <sys/epoll.h>

struct	sockaddr_in;
struct	epoll_event;

class Server {
public:
	~Server( void );
	
	static Server*	instantiate( void );

	void			startServer(int port);
	void			runServer( void );
	void			sendError(int ClientId, int codeError, const std::string& msgError);

	void			serverRequest(int clientID, std::string rawLine);

	void			LegacysendToChannel(std::string channelName, int clientID, std::string message);
	void			LegacysendToServer(int clientID, std::string message);

	void			processCommand(Command* command);

	void			sendToConsole(int clientID, std::string message);
	void			sendToServer(int clientID, std::string message);
	void			sendToChannel(int clientID, std::string channelName, std::string message);
	void			sendToClient(int clientID, int targetID, std::string message);
	
	void			addChannel(t_channelType channelType, std::string channelName);
	void			eraseChannel(std::string channelName);


private:
	Server( void );
	Server(Server const & src);
	Server&	operator=(Server const & rhs);

	void	addClient( void );
	void	eraseClient(int clientID);

	std::string const	_serverName;

	static Server*					_me;
	Client*							_console;

	int								_port;
	int								_mySocket;
	int								_epollfd;
	unsigned int					_serverLen;
	sockaddr_in*					_address;
	epoll_event						_ev;
	std::map<int, Client*>			_serverClient;
	std::map<int, Client*>			_serverOperator;
	std::map<std::string, Channel*>	_serverChannel;

	class Factory : public Client, public Channel {
	public:
		static Client*		createClient(int clientID);
		static Channel*		createChannel(t_channelType channelType, std::string channelName);
		static void			deleteClient(Client* oldClient);
		static void			deleteChannel(Channel* oldChannel);

	private:
		Factory( void );
		~Factory( void );
		Factory(Factory const & src);
		Factory&	operator=(Factory const & rhs);
	};
};

#endif
