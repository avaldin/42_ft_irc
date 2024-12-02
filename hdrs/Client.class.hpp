/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:47:02 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/02 09:49:16 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CLASS_HPP
# define CLIENT_CLASS_HPP
# include <string>

class Client {
public:
	~Client( void );
	Client(int clientID);
	
	void	action( void );

	
	std::string	getUsername( void ) const;
	int			getClientID( void ) const;
	bool		getRegistered( void ) const;

private:
	Client( void );
	Client(Client const & src);
	Client&	operator=(Client const & rhs);
	int const			_clientID;
	std::string const	_username;
	bool				_registered;
};

#endif
