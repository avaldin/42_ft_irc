/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:43:48 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/28 20:37:33 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CLASS_HPP
# define SERVER_CLASS_HPP
# define nullptr 0

# include <map>
# include <string>
# include <sys/epoll.h>

class	Client;
struct	sockaddr_in;
struct	epoll_event;

class Server {
public:
	~Server( void );
	
	static Server*	instanciate( void );
	void			startServer(int port);
	void			runServer( void );
	void			sendToServer(int clientID, std::string token);

	sockaddr_in*	getAddress( void );
	int				getSocketID( void );
	unsigned int	getServerLen( void );
	
	static Server*			_me;

private:
	Server( void );
	Server(Server const & src);
	Server&	operator=(Server const & rhs);

	void	addClient( void );
	void	deleteClient(int clientID);

	int						_port;
	int						_mySocket;
	int						_epollfd;
	unsigned int			_serverLen;
	sockaddr_in*			_address;
	epoll_event				_ev, _events[10];
	std::map<int, Client *>	_clientDatabase;
};

#endif