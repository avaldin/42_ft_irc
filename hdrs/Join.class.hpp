/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:59:40 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/17 11:26:29 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_CLASS_HPP
# define JOIN_CLASS_HPP
# include "ACommand.class.hpp"
# include <vector>
# define CHECK_JOIN 6

class Client;
class Channel;
class Server;

class Join : public ACommand {
public :
	void	execute(Client& client);
	
private:
	Join( void ) : _cmdName("JOIN") {}
	~Join( void ) {}
	
	typedef struct	s_data {
		Client*			client;
		Channel*		targetChannel;
		std::string		targetName;
		std::string		targetKey;
		std::string		error;
		int				sizeKey;
		int				idxKey;
	}	t_data;

	void	checkRegistered(t_data& myData);
	void	checkParams(t_data& myData);
	void	checkChannelName(t_data& myData);
	void	checkChannelKey(t_data& myData);
	void	checkChannelInvite(t_data& myData);
	void	checkChannelFilling(t_data& myData);

	void	createChannel(t_data& myData);
	void	joinChannel(t_data& myData);

	void	RPL_join(t_data& myData);

	std::string const			_cmdName;
	std::vector<std::string>	_targetChannels;
	std::vector<std::string>	_targetKeys;

	static Server*	_server;
	
	static void(Join::*_method[CHECK_JOIN])(t_data&);

friend class Command;
};

#endif
