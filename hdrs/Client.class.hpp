/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:47:02 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/30 20:20:18 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CLASS_HPP
# define CLIENT_CLASS_HPP
# include <string>
# include "Channel.class.hpp"

class Client {
public:
	virtual ~Client( void );
	
	void	action( void );
	
	std::string	getnickname( void );
	int			getClientID( void );

protected:
	Client( void );
	Client(int clientID, std::string nickname);
	Client(Client const & src);

	Client&	operator=(Client const & rhs);

	static Client*	instantiate(int clientID, std::string nickname);

	int const			_clientID;
	std::string const	_nickname;
	Channel*			_actualChannel;
};

#endif
