/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:47:02 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/28 20:30:40 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CLASS_HPP
# define CLIENT_CLASS_HPP
# include <string>

class Client {
public:
	~Client( void );
	Client(int clientID, std::string username);
	
	void	action( void );
	
	std::string	getUsername( void );
	int			getClientID( void );
	
private:
	Client( void );
	Client(Client const & src);
	Client&	operator=(Client const & rhs);
	int const			_clientID;
	std::string const	_username;
};

#endif
