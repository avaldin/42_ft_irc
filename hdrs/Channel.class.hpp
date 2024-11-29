/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:37:21 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/29 20:00:45 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_CLASS_HPP
# define CHANNEL_CLASS_HPP
# include <map>
# include <string>

class Client;

class Channel {
public:
	Channel( void );
	~Channel( void );
	Channel(Channel const & src);

	Channel&	operator=(Channel const & rhs);
	
	void	sendToChannel(int clientID, std::string token);

private:
	int						_channelID;
	std::map<int, Client*>	_channelClient;
};

#endif
