/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Send.namespace.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:55:20 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/02 14:51:12 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEND_NAMESPACE_HPP
# define SEND_NAMESPACE_HPP

#include <map>
#include <string>

class Client;
class Channel;

namespace Send {
	void	ToConsole(int const & targetID, std::string const & message);
	void	ToServer(std::map<int, Client*>& serverClient, std::string const & message);
	void	ToChannel(Channel const & channel, std::string const & message);
	void	ToClient(int const & targetID, std::string const & message);
}

#endif
