/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:43:48 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/20 18:43:41 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CLASS_HPP
# define SERVER_CLASS_HPP
# define nullptr 0

#include "Client.class.hpp"
#include "Channel.class.hpp"

# include <map>
# include <list>
# include <string>
# include <sys/epoll.h>

#include <stdio.h>

struct	sockaddr_in;
struct	epoll_event;

class	Parser;

class Server {
public:
	~Server( void );
	
	static Server*	instantiate( void );

	void			startServer(int port, const std::string& password);
	void			runServer( void );
	void 			closeServer();

	void			serverRequest(Client& client, std::string rawLine);

	// void			LegacysendToChannel(std::string channelName, int clientID, std::string message);
	// void			LegacysendToServer(int clientID, std::string message);

private:

	Server( void );

	// void	processCommand(ACommand* command);

	// void		debugPrintServer( void ) const;

	void		addClient( void );
	void		eraseClient(int const & clientID);
	void		addChannel(t_channelType channelType, std::string channelName);
	void		eraseChannel(std::string channelName);
	Client*		findClientNickname(std::string const & nickname);
	Client*		findClientUsername(std::string const & username);
	Client*		findClientId(int const & id);

	void		signalHandler( void );

	std::string const					_serverName;
	std::string							_serverPassword;

	static Server*						_me;
	Client*								_console;
	
	int									_port;
	int									_mySocket;
	int									_epollfd;
	int 								_signalfd;
	unsigned int						_serverLen;
	sockaddr_in*						_address;
	epoll_event							_ev;
	std::map<int, Client*>				_serverClientId;
	std::map<int, Client*>				_serverOperator;
	std::map<std::string, Channel*>		_serverChannel;

	class Factory : public Client, public Channel {
	public:
		static Client*		createClient(int clientID);
		static Channel*		createChannel(t_channelType channelType, std::string channelName);
		static void			deleteClient(Client* oldClient);
		static void			deleteChannel(Channel* oldChannel);

	private:
		Factory( void );
		~Factory( void );
	};
	
friend class Mode;
friend class Invite;
friend class Topic;
friend class Kick;
friend class Pass;
friend class Nick;
friend class User;
friend class Join;
friend class Privmsg;
friend class Quit;

};


#endif
