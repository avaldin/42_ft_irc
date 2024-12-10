/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.define.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:38:55 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/10 15:45:21 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_DEFINE_HPP
# define ERROR_DEFINE_HPP
# include <string>

# define	ERR_NOSUCHNICK(nickname) ("401 :" + (nickname) + " :No such nick/channel\r\n")
// Used to indicate the nickname parameter supplied to a command is currently
// unused.

# define ERR_NOSUCHCHANNEL(channel) ("403 :" + (channel) + " :No such channel\r\n")
// Used to indicate the given channel name is invalid

# define ERR_TOOMANYCHANNELS(channel) ("405 :" + (channel) + " :You have joined too many channels\r\n")
// Sent to a user when they have joined the maximum number of allowed channels
// and they try to join another channel.

# define ERR_TOOMANYTARGETS(target) ("407 :" + (target) + " :Duplicate recipients. No message delivered\r\n")
// Returned to a client which is attempting to send a PRIVMSG/NOTICE using the
// user@host destination format and for a user@host which has several occurrences.

# define ERR_UNKNOWNCOMMAND(command) ("421 :" + (command) + " :Unknown command\r\n")
// Returned to a registered client to indicate that the command send unknown
// by the server

# define ERR_NONICKNAMEGIVEN "431 :No Nickname given\r\n"
// Returned when a nickname parameter expected for a command and isn't found.

# define ERR_ERRONEUSNICKNAME(nickname) ("432 :" + (nickname) + " :Erroneus nickname\r\n")
// Returned after receiving a NICK message which contains characters which do
// not fall in the defined set. See section x.x.x for details on valid nicknames.

# define ERR_NICKNAMEINUSE(nickname) ("433 :" + (nickname) + " :Nickname is already in use\r\n")
// Returned when a NICK message is processed that results in an attempt to
// change to a currently existing nickname.

# define ERR_NICKCOLLISION(nickname) ("436 :" + (nickname) +  ":Nickname collision KILL\r\n")
// Returned by a server to a client when it detects a nickname collision
// (registered of a NICK that already exists by another server).

# define ERR_USERNOTINCHANNEL(nickname, channel) ("441 :" + (nickname) + " " + (channel) + " :They aren't on that channel\r\n")
// Returned by the server to indicate that the targer user of the commande is
// not on the given channel

# define ERR_NOTONCHANNEL(channel) ("442 :" + (channel) + " :You're not on that channel\r\n")
// Returned by the server whenever a client tries to preform a channel effecting
// command for which to client isn't a member.

# define ERR_USERONCHANNEL(username, channel) ("443 :" + (user) + " " + (channel) + " :is already on channel\r\n")
// 443 Returned when a client tries to invite a user to a channel they are already on.

# define ERR_SUMMONDISABLED "445 :SUMMON has been disabled\r\n"
// Returned as a response to the SUMMON command. Must be returned by any server
// which does not implement it. 

# define ERR_USERSDISABLED "446 :USERS has been disabled\r\n"
// Returned as a response to the USERS command.  Must be returned by any server
// which does not implement it.

# define ERR_NOTREGISTRATED "451 :You have not registered\r\n"
// Returned by the server to indicate that the client must be registered before
// the server will allow it to be parsed in detail.

# define ERR_NEEDMOREPARAMS(command) ("461 :" + (command) + " :Not enough parameters\r\n")
// Returned by the server by numerous commands to indicate to the client that
// it didn't supply enough parameters.

# define ERR_ALREADYREGISTRED "462 :You may not reregister\r\n"
// Returned by the server to any link which tries to change part of the
// registered details (such as password or user details from second USER message).

# define ERR_PASSWDMISMATCH "464 :Password incorrect\r\n"
// Returned to indicate a failed attempt at registering a connection for which
// a password was required and was either not given or incorrect.

# define ERR_YOUREBANNEDCREEP "465 :You are banned from this server\r\n"
// Returned after an attempt to connect and register yourself with a server
// which has been setup to explicitly deny connections to you.

# define ERR_KEYSET(channel) ("467 :" + (channel) + " :Channel key already set\r\n") 

# define ERR_CHANNELISFULL(channel) ("471 :" + (channel) + " :Cannot join channel (+l)\r\n")

# define ERR_UNKNOWNMODE(char) ("472 :" + (char) +  ":is unknown mode char to me\r\n") 

# define ERR_INVITEONLYCHAN(channel) ("473 :" + (channel) + " :Cannot join channel (+i)\r\n")

# define ERR_BANNEDFROMCHAN(channel) ("474 :" + (channel) + " :Cannot join channel (+b)\r\n")

# define ERR_BADCHANNELKEY(channel) ("475 :" + (channel) + " :Cannot join channel (+k)\r\n")

# define ERR_NOPRIVILEGES "481 :Permission Denied- You're not an IRC operator\r\n"
// Any command requiring operator privileges to operate must return this
// error to indicate the attempt was unsuccessful.

# define ERR_CHANOPRIVSNEEDED(channel) ("482 :" + (channel) + " :You're not channel operator\r\n")
// Any command requiring 'chanop' privileges (such as MODE messages) must
// return this error if the client making the attempt is not a chanop on the
// specified channel.

# define ERR_CANTKILLSERVER "483 :You cant kill a server!\r\n"
// Any attempts to use the KILL command on a server are to be refused and
// this error returned directly to the client.

# define ERR_NOOPERHOST "491 :No O-lines for your host\r\n"
// If a client sends an OPER message and the server has not been configured
// to allow connections from the client's host as an operator, this error must be returned.

# define ERR_UMODEUNKNOWNFLAG "501 :Unknown MODE flag\r\n"
// Returned by the server to indicate that a MODE message was sent with a
// nickname parameter and that the a mode flag sent was not recognized.

# define ERR_USERSDONTMATCH "502 :Cant change mode for other users\r\n"
// Error sent to any user trying to view or change the user mode for a user
// other than themselves.

#endif