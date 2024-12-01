/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:47:02 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/01 19:33:20 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CLASS_HPP
# define CLIENT_CLASS_HPP
# include <string>
# include "Channel.class.hpp"

class Client {
public:

	void	action( void );
	
	int const			_clientID;
	std::string const	_nickname;
	std::string			_actualChannel;

protected:
	Client( void );
	virtual ~Client( void );

	static Client*	instantiateClient(int clientID, std::string nickname);
	static void		uninstantiateClient(Client* oldClient);

private:
	Client(Client const & src);
	Client(int clientID, std::string nickname);
	Client&	operator=(Client const & rhs);
};

#endif
