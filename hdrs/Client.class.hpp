/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:47:02 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/09 13:03:33 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CLASS_HPP
# define CLIENT_CLASS_HPP
# include <string>

typedef enum RegisterState {
	NOT_REGISTERED,
	PASS,
	NICK,
	USER,
	REGISTERED
};

class Client {
public:
	~Client( void );
	Client(int clientID);
	
	void	action( void );

	
	std::string		getUsername( void ) const;
	int				getClientID( void ) const;
	RegisterState	getRegistered( void ) const;
	void 			setRegistered(bool registered);
	void			setNickname(const std::string&	nickname);

private:
	Client( void );
	Client(Client const & src);
	Client&	operator=(Client const & rhs);
	int const			_clientID;
	std::string const	_username;
	std::string			_nickname;
	RegisterState		_registered;
};

#endif
