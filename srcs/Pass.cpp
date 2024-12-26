/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:20:39 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/26 15:21:31 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.class.hpp"
#include "Error.define.hpp"
#include "Server.class.hpp"
#include "Send.namespace.hpp"

#include "Client.class.hpp"

Server*	Pass::_server = Server::instantiate();

Pass::Pass( void ) : _cmdName("PASS") {
	return ;
}

Pass::~Pass( void ) {
	return ;
}

void	Pass::execute(Client const & client) {
	
}