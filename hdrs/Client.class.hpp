/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:47:02 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/02 14:08:29 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CLASS_HPP
# define CLIENT_CLASS_HPP
# include <string>

typedef enum RegisterState {
	NOT_REGISTERED,
	PASS,

};

class Client {
public:
	~Client( void );
	Client(int clientID);
	
	void	action( void );

	
	std::string	getUsername( void ) const;
	int			getClientID( void ) const;
	bool		getRegistered( void ) const;
	void setRegistered(bool registered);

private:
	Client( void );
	Client(Client const & src);
	Client&	operator=(Client const & rhs);
	int const			_clientID;
	std::string const	_username;
	bool				_registered;
};

#endif
