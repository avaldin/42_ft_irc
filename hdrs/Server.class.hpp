/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:43:48 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/01 19:58:16 by tmouche          ###   ########.fr       */
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

	void			sendToServer(int clientID, std::string message);
	void			sendToChannel(std::string channelName, int clientID, std::string message);
	// void			sendToClient(int senderID, int receiverID, std::string message);
	// void			serverRequest(std::string channelName, int clientID, std::string rawLine);
	
	void			addChannel(t_channelType channelType, std::string channelName);
	void			eraseChannel(std::string channelName);


private:
	Server( void );
	Server(Server const & src);
	Server&	operator=(Server const & rhs);

	void	addClient( void );
	void	eraseClient(int clientID);

	static Server*			_me;

	int						_port;
	int						_mySocket;
	int						_epollfd;
	unsigned int			_serverLen;
	sockaddr_in*			_address;
	epoll_event				_ev;
	std::map<int, Client*>	_serverClient;
	std::map<int, Client*>	_serverOperator;
	std::map<std::string, Channel*>	_serverChannel;

	class Factory : public Client, public Channel {
	public:
		static Client*		createClient(int clientID, std::string nickname);
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