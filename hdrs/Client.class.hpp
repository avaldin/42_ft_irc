/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:47:02 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/02 15:33:03 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CLASS_HPP
# define CLIENT_CLASS_HPP
# include "Channel.class.hpp"
# include <string>
# include <vector>

class Client {
public:

	void	action( void );
	
	int const					_clientID;
	std::string					_username;
	std::string 				_nickname;

	void	addChannel(std::string newChannel);

protected:
	Client( void );
	virtual ~Client( void );

	static Client*	instantiateClient(int clientID);
	static void		uninstantiateClient(Client* oldClient);

private:
	Client(Client const & src);
	Client(int clientID);
	Client&	operator=(Client const & rhs);

	std::vector<std::string>	_actualChannel;
};

#endif

