/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.define.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 13:38:55 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/09 17:56:25 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_DEFINE_HPP
# define ERROR_DEFINE_HPP
# include <string>

std::string	ERR_NOSUCHNICK(std::string const nickname) {return (nickname + " :No such nick/channel");} 
// 401 Used to indicate the nickname parameter supplied to a command is currently
// unused.

std::string	ERR_NOSUCHCHANNEL(std::string const channelName) {return (channelName + " :No such channel");}
// 403 Used to indicate the given channel name is invalid

std::string	ERR_TOOMANYCHANNELS(std::string const channelName) {return (channelName + " :You have joined too many channels");}
// 405 Sent to a user when they have joined the maximum number of allowed channels
// and they try to join another channel.

std::string	ERR_TOOMANYTARGETS(std::string const target) {return (target + " :Duplicate recipients. No message delivered");}
// 407 Returned to a client which is attempting to send a PRIVMSG/NOTICE using the
// user@host destination format and for a user@host which has several occurrences.

std::string	ERR_UNKNOWNCOMMAND(std::string const command) {return (command + " :Unknown command");}
// 421 Returned to a registered client to indicate that the command send unknown
// by the server

std::string	ERR_NONICKNAMEGIVEN( void ) {return ":No nickname given";}
// 431 Returned when a nickname parameter expected for a command and isn't found.

std::string	ERR_ERRONEUSNICKNAME(std::string const nick) {return (nick + " :Erroneus nickname");}
// 432 Returned after receiving a NICK message which contains characters which do
// not fall in the defined set. See section x.x.x for details on valid nicknames.

std::string	ERR_NICKNAMEINUSE(std::string const nick) {return (nick + " :Nickname is already in use");} 
// 433 Returned when a NICK message is processed that results in an attempt to
// change to a currently existing nickname.

std::string	ERR_NICKCOLLISION(std::string const nick) {return (nick + " :Nickname collision KILL");}
// 436 Returned by a server to a client when it detects a nickname collision
// (registered of a NICK that already exists by another server).

std::string	ERR_USERNOTINCHANNEL(std::string const nick, std::string channel) {return (nick + " " + channel + " :They aren't on that channel");}
// 441 Returned by the server to indicate that the targer user of the commande is
// not on the given channel

std::string	ERR_NOTONCHANNEL(std::string const channel) {return (channel + " :You're not on that channel");}
// 442 Returned by the server whenever a client tries to preform a channel effecting
// command for which to client isn't a member.

std::string	ERR_USERONCHANNEL(std::string const user, std::string channel) {return (user + " " + channel + " :is already on channel");}
// 443 Returned when a client tries to invite a user to a channel they are already on.

std::string	ERR_SUMMONDISABLED( void ) {return ":SUMMON has been disabled";}
// 445 Returned as a response to the SUMMON command. Must be returned by any server
// which does not implement it. 

std::string	ERR_USERSDISABLED( void ) {return ":USERS has been disabled";}
// 446 Returned as a response to the USERS command.  Must be returned by any server
// which does not implement it.

std::string	ERR_NOTREGISTRATED( void ) {return ":You have not registered";}
// 451 Returned by the server to indicate that the client must be registered before
// the server will allow it to be parsed in detail.

std::string	ERR_NEEDMOREPARAMS(std::string const command) {return (command + " :Not enough parameters");}
// 461 Returned by the server by numerous commands to indicate to the client that
// it didn't supply enough parameters.

std::string	ERR_ALREADYREGISTRED( void ) {return ":You may not reregister";}
// 462 Returned by the server to any link which tries to change part of the
// registered details (such as password or user details from second USER message).

std::string	ERR_PASSWDMISMATCH( void ) {return ":Password incorrect";}
// 464 Returned to indicate a failed attempt at registering a connection for which
// a password was required and was either not given or incorrect.

std::string	ERR_YOUREBANNEDCREEP( void ) {return ":You are banned from this server";}
// 465 Returned after an attempt to connect and register yourself with a server
// which has been setup to explicitly deny connections to you.

std::string	ERR_KEYSET(std::string const channel) {return (channel + " :Channel key already set");}
// 467

std::string	ERR_CHANNELISFULL(std::string const channel) {return (channel + " :Cannot join channel (+l)");}
// 471

std::string	ERR_UNKNOWNMODE(std::string const c) {return (c + " :is unknown mode char to me");}
// 472

std::string	ERR_INVITEONLYCHAN(std::string const channel) {return (channel + " :Cannot join channel (+i)");}
// 473

std::string	ERR_BANNEDFROMCHAN(std::string const channel) {return (channel + " :Cannot join channel (+b)");}
// 474 

std::string	ERR_BADCHANNELKEY(std::string const channel) {return (channel + " :Cannot join channel (+k)");}
// 475

std::string	ERR_NOPRIVILEGES( void ) {return ":Permission Denied- You're not an IRC operator";}
// 481 Any command requiring operator privileges to operate must return this
// error to indicate the attempt was unsuccessful.

std::string	ERR_CHANOPRIVSNEEDED(std::string const channel) {return (channel + " :You're not channel operator");}
// 482 Any command requiring 'chanop' privileges (such as MODE messages) must
// return this error if the client making the attempt is not a chanop on the
// specified channel.

std::string	ERR_CANTKILLSERVER( void ) {return ":You cant kill a server!";}
// 483 Any attempts to use the KILL command on a server are to be refused and
// this error returned directly to the client.

std::string	ERR_NOOPERHOST( void ) {return ":No O-lines for your host";} 
// 491 If a client sends an OPER message and the server has not been configured
// to allow connections from the client's host as an operator, this error must be returned.

std::string	ERR_UMODEUNKNOWNFLAG( void ) {return ":Unknown MODE flag";}
// 501 Returned by the server to indicate that a MODE message was sent with a
// nickname parameter and that the a mode flag sent was not recognized.

std::string	ERR_USERSDONTMATCH( void ) {return ":Cant change mode for other users";}
// 502 Error sent to any user trying to view or change the user mode for a user
// other than themselves.

#endif