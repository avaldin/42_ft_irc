/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.define.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:38:55 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/22 10:28:09 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_DEFINE_HPP
# define ERROR_DEFINE_HPP
# include <string>
# define ERR_NOSUCHNICK(target, nick) (":IRC_serv 401 " + (target) + " " + (nick) + " :No such nick")
// Used to indicate the nickname parameter supplied to a command is currently
// unused.

# define ERR_NOSUCHCHANNEL(target, channel) (":IRC_serv 403 " + (target) + " " + (channel) + " :No such channel")
// Used to indicate the given channel name is invalid

#define ERR_CANNOTSENDTOCHAN(target, channel) (":IRC_serv 404 " + (target) + " " + (channel) + " :Cannot send to channel")
//This is returned when a message to a channel is blocked by a channel mode or ban

# define ERR_TOOMANYCHANNELS(target, channel) (":IRC_serv 405 " + (target) + " " + (channel) + " :You have joined too many channels")
// Sent to a user when they have joined the maximum number of allowed channels
// and they try to join another channel.

# define ERR_TOOMANYTARGETS(target) ("407 :" + (target) + " :Duplicate recipients. No message delivered\r\n") // pas sur le site
// Returned to a client which is attempting to send a PRIVMSG/NOTICE using the
// user@host destination format and for a user@host which has several occurrences.

# define ERR_NORECIPIENT(target, command) (":IRC_serv 411 " + (target) + " :No recipient given (" + (command) + ")")
// Returned by the PRIVMSG command to indicate the message wasn’t delivered
// because there was no recipient given.

# define ERR_NOTEXTTOSEND(target) (":IRC_serv 412 " + (target) + " :No text to send")
// Returned by the PRIVMSG command to indicate the message wasn’t delivered
// because there was no text to send.

# define ERR_UNKNOWNCOMMAND(target, command) (":IRC_serv 421 " + (target) + " " + (command) + " :Unknown command")
// Returned to a registered client to indicate that the command send unknown
// by the server

# define ERR_NONICKNAMEGIVEN (":IRC_serv 431 " + (target) + " :No nickname given")
// Returned when a nickname parameter expected for a command and isn't found.

# define ERR_ERRONEUSNICKNAME(target, nick) (":IRC_serv 432 " + (target) + " " + (nick) + " :Erroneous Nickname")
// Returned after receiving a NICK message which contains characters which do
// not fall in the defined set. See section x.x.x for details on valid nicknames.

# define ERR_NICKNAMEINUSE(target, nick) (":IRC_serv 433 " + (target) + " " + (nick) + " :Nickname is already in use.")
// Returned when a NICK message is processed that results in an attempt to
// change to a currently existing nickname.

# define ERR_NICKCOLLISION(target, nick) (":IRC_serv 436 " + (target) + " " + (nick) + " :Nickname collision KILL") //jsp pour le kill
// Returned by a server to a client when it detects a nickname collision
// (registered of a NICK that already exists by another server).

# define ERR_USERNOTINCHANNEL(target, nick, channel) (":IRC_serv 441 " + (target) + " " + (nick) + " " + (channel) + " :They aren't on that channel")
// Returned by the server to indicate that the targer user of the commande is
// not on the given channel

# define ERR_NOTONCHANNEL(target, channel) (":IRC_serv 442 " + (target) + " " + (channel) + " :You're not on that channel")
// Returned by the server whenever a client tries to preform a channel effecting
// command for which to client isn't a member.

# define ERR_USERONCHANNEL(target, nick, channel) (":IRC_serv 443 " + (target) + " " + (nick) + " " + (channel) + " :is already on channel")
// 443 Returned when a client tries to invite a user to a channel they are already on.

# define ERR_SUMMONDISABLED "445 :SUMMON has been disabled\r\n" //pas sur le site
// Returned as a response to the SUMMON command. Must be returned by any server
// which does not implement it. 

# define ERR_USERSDISABLED "446 :USERS has been disabled\r\n" //pas sur le site
// Returned as a response to the USERS command.  Must be returned by any server
// which does not implement it.

# define ERR_NOTREGISTRATED(target) (":IRC_serv 451 " + (target) + " :Register first.")
// Returned by the server to indicate that the client must be registered before
// the server will allow it to be parsed in detail.

# define ERR_NEEDMOREPARAMS(target, command) (":IRC_serv 461 " + (target) + " " + (command) + " :Not enough parameters") // manque param en paramettre a voir
// Returned by the server by numerous commands to indicate to the client that
// it didn't supply enough parameters.

# define ERR_ALREADYREGISTRED(target) (":IRC_serv 462 " + (target) + " :You may not reregister")
// Returned by the server to any link which tries to change part of the
// registered details (such as password or user details from second USER message).

# define ERR_PASSWDMISMATCH(target) (":IRC_serv 464 " + (target) + " :Password Incorrect")
// Returned to indicate a failed attempt at registering a connection for which
// a password was required and was either not given or incorrect.

# define ERR_YOUREBANNEDCREEP(target, reason) (":IRC_serv 465 " + (target) + " :" + (reason))
// which has been setup to explicitly deny connections to you.

# define ERR_KEYSET(target, channel) (":IRC_serv 467 " + (target) + " " + (channel) + " :Channel key already set")

# define ERR_CHANNELISFULL(target, channel) (":IRC_serv 471 " + (target) + " " + (channel) + " :Cannot join channel, channel is full (+l)")

# define ERR_UNKNOWNMODE(target, mode) (":IRC_serv 472 " + (target) + " " + (mode) + " :is unknown mode char to me")

# define ERR_INVITEONLYCHAN(target, channel) (":IRC_serv 473 " + (target) + " " + (channel) + " :Cannot join channel, you must be invited (+i)")

# define ERR_BANNEDFROMCHAN(target, channel) (":IRC_serv 474 " + (target) + " " + (channel) + " :Cannot join channel, you are banned (+b)")

# define ERR_BADCHANNELKEY(target, channel) (":IRC_serv 475 " + (target) + " " + (channel) + " :Cannot join channel, you need the correct key (+k)")

# define ERR_BADCHANMASK(target, channel) (":IRC_serv 476 " + (target) + " " + (channel) + " :Bad Channel Mask") // pas sur le site

# define ERR_NOPRIVILEGES(target) (":IRC_serv 481 " + (target) + " :Permission Denied: Insufficient privileges")
// Any command requiring operator privileges to operate must return this
// error to indicate the attempt was unsuccessful.

# define ERR_CHANOPRIVSNEEDED(target, channel) (":IRC_serv 482 " + (target) + " " + (channel) + " :You're not channel operator")
// Any command requiring 'chanop' privileges (such as MODE messages) must
// return this error if the client making the attempt is not a chanop on the
// specified channel.

# define ERR_CANTKILLSERVER(target) (":IRC_serv 483 " + (target) + " :You cant kill a server!")
// Any attempts to use the KILL command on a server are to be refused and
// this error returned directly to the client.

# define ERR_NOOPERHOST(target) (":IRC_serv 491 " + (target) + " :No Operator block for your host")
// If a client sends an OPER message and the server has not been configured
// to allow connections from the client's host as an operator, this error must be returned.

# define ERR_UMODEUNKNOWNFLAG(target, mode) (":IRC_serv 501 " + (target) + " " + (mode) + " :Unknown MODE flag")
// Returned by the server to indicate that a MODE message was sent with a
// nickname parameter and that the a mode flag sent was not recognized.

# define ERR_USERSDONTMATCH(target) (":IRC_serv 502 " + (target) + " :Cant change mode for other users")
// Error sent to any user trying to view or change the user mode for a user
// other than themselves.

#endif