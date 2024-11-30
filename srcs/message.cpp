/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:03:42 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/29 17:09:22 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exception.class.hpp"

#include <string>
#include <vector>
#include <sys/socket.h>
#include <cstring>

std::string my_recv(int id)
{
	std::string			ret;
	std::vector<char>	buffer(512);
	ssize_t				bytesReceived = 0;

	do
	{
		bytesReceived = recv(id, &buffer[0], buffer.size(), 0);
		if (bytesReceived == -1)
			throw RecvException();
		ret.append(&buffer[0], bytesReceived);
	}
	while(ret.find('\n') == std::string::npos);
	return (ret);
}
