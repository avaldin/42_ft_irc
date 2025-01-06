/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:47:02 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/03 14:00:02 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CLASS_HPP
# define CLIENT_CLASS_HPP
# include "Channel.class.hpp"
# include <string>
# include <vector>

typedef enum s_registeredState {
	NOT_REGISTERED,
	ONGOING_REGISTERING,
	REGISTERED
}			t_registeredState;

class Client {
public:

	void	action( void );
	
	int const					_clientID;
	std::string					_username;
	std::string 				_nickname;
	std::string					_prefix;
	t_registeredState			status;
	unsigned int				_lastPing; //initialiser au prochain ping

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
