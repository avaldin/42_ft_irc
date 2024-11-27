/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:43:48 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/27 20:57:35 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CLASS_HPP
# define SERVER_CLASS_HPP
# define nullptr 0
# include <sys/socket.h>
# include <netinet/in.h>

class Server {
public:
	~Server( void );
	
	void			startServer(int port);
	static Server*	instanciate( void );
	
	struct sockaddr_in*	getAddress( void );
	int					getSocketID( void );
	
	static Server*		_me;
private:
	Server( void );
	Server(Server const & src);
	Server&	operator=(Server const & rhs);

	int					_port;
	int					_mySocket;
	struct sockaddr_in	_address;
};

#endif