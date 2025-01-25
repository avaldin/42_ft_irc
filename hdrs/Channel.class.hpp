/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:37:21 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/25 17:50:56 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_CLASS_HPP
# define CHANNEL_CLASS_HPP
# include <map>
# include <string>
# include "Duelbot.class.hpp"

class Client;

typedef enum	e_channelType {
	MODE,
	NOMODE,
	SAFE
}				t_channelType;

class Channel {
public:

	void			sendToChannel(std::string const message) const;
	void			privMsgToChannel(std::string const message, int clientID) const;
	bool			isOperator(int const clientID);
	bool			isInvited(int const clientID);
	bool			isClient(int const clientID);
	bool			isClient(std::string const clientID);
	void			addClient(int const clientID, Client const * client);
	void			deleteClient(int const clientID);
	void			addInvited(int const clientID, Client const * client);
	void			deleteInvited(int const clientID);
	void			addOperator(int const clientID);
	void			deleteOperator(int const clientID);

	t_channelType const		_channelType;
	std::string const		_channelName;

	unsigned int			_channelLimit;
	std::string				_channelPassword;
	std::string				_channelTopic;
	bool					_topicMode;
	bool					_inviteOnlyMode;

	Duelbot					_myBot;

protected:
	Channel( void );
	virtual ~Channel( void );

	static Channel*	instantiateChannel(t_channelType type, std::string channelName);
	static void		uninstantiateChannel(Channel* oldChannel);
	
private:
	Channel(Channel const & src);
	Channel(t_channelType channelType, std::string channelName);

	Channel&	operator=(Channel const & rhs);
	
	std::map<int, Client const *>	_channelClient;
	std::map<int, Client const *>	_channelOperator;
	std::map<int, Client const *>	_channelCreator;
	std::map<int, Client const *>	_invitedClient;

friend class Join;
friend class Duelbot;
};

#endif
