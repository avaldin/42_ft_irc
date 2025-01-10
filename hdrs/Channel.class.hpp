/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:37:21 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/10 18:50:07 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_CLASS_HPP
# define CHANNEL_CLASS_HPP
# include <map>
# include <string>

class Client;

typedef enum	e_channelType {
	MODE,
	NOMODE,
	SAFE
}				t_channelType;

class Channel {
public:

	void			debugPrintChannel( void ) const;

	void			sendToChannel(std::string const message) const;
	bool			isOperator(int const clientID);
	bool			isInvited(int const clientID);
	bool			isClient(int const clientID);
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

protected:
	Channel( void );
	virtual ~Channel( void );

	static Channel*	instantiateChannel(t_channelType type, std::string channelName);
	static void		uninstantiateChannel(Channel* oldChannel);
	
private:
	Channel(Channel const & src);
	Channel(t_channelType channelType, std::string channelName);

	Channel&	operator=(Channel const & rhs);

	std::map<int, Client const *>			_channelClient;
	std::map<int, Client const *>			_channelOperator;
	std::map<int, Client const *>			_channelCreator;
	std::map<int, Client const *>			_invitedClient;

friend class Join;
};

#endif
