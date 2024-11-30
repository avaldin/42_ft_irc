/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:37:21 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/30 20:51:34 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_CLASS_HPP
# define CHANNEL_CLASS_HPP
# include <map>
# include <string>

class Client;

class Channel {
public:
	virtual ~Channel( void );

	
	void	sendToChannel(int const clientID, std::string const message);
	bool	isOperator(int const clientID);

protected:
	Channel( void );
	Channel(int channelID, std::string channelName);
	Channel(Channel const & src);

	Channel&	operator=(Channel const & rhs);
	
	static Channel*	instantiate(int channelID, std::string channelName);

private:
	int const				_channelID;
	std::string const		_channelName;
	
	// unsigned int			_channelLimit;
	// std::string				_channelPassword;
	// std::string				_channelTopic;

	// bool					_topicMode;
	// bool					_inviteOnlyMode;

	std::map<int, Client*>	_channelClient;
	std::map<int, Client*>	_channelOperator;
	
};

#endif
