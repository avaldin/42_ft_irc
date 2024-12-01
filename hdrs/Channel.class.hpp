/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:37:21 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/01 19:33:15 by tmouche          ###   ########.fr       */
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

	void			sendToChannel(int const clientID, std::string const message);
	bool			isOperator(int const clientID);

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

	std::map<int, Client*>	_channelClient;
	std::map<int, Client*>	_channelOperator;
	std::map<int, Client*>	_channelCreator;
};

#endif
