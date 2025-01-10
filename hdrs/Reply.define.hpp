/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.define.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:23:27 by tmouche           #+#    #+#             */
/*   Updated: 2024/12/18 16:11:43 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_DEFINE_HPP
# define REPLY_DEFINE_HPP

#define RPL_NONE
// 300 Dummy reply number. Not used.

#define RPL_WELCOME(prefix) ("001 :Welcome to the Internet Relay Network " + (prefix) + "\r\n")
// Message displayed to the client when he registered successfully

#define RPL_AWAY(nick, awayMessage) ("301 :" + (nick) + " :" + (awayMessage) + "\r\n")

#define RPL_UNAWAY "305 :You are no longer marked as being away\r\n"

#define RPL_NOWAWAY "306 :You have been marked as being away\r\n"
// These replies are used with the AWAY command (if allowed).
// RPL_AWAY is sent to any client sending a PRIVMSG to a client which is away.
// RPL_AWAY is only sent by the server to which the client is connected. Replies
// RPL_UNAWAY and RPL_NOWAWAY are sent when the client removes and sets an AWAY message.

#define RPL_WHOISUSER(nick, user, host, realName) ("311 :" + (nick) + " " + (user) + " "+ (host) + " * :" + (realName) + "\r\n")

#define RPL_WHOISSERVER(nick, server, serverInfo) ("312 :" + (nick) + " " + (server) + " " + (serverInfo) + "\r\n")

#define RPL_WHOISOPERATOR(nick) ("313 :" + (nick) + ": is an IRC operator\r\n")

#define RPL_WHOISIDLE(nick, integer) ("317 :" + (nick) + " " + (integer) + " :seconds idle\r\n")

#define RPL_ENDOFWHOIS(nick) ("318 :" + (nick) + " :End of /WHOIS list\r\n")

#define RPL_WHOISCHANNELS(nick, channel, space) ("319 :" + (nick) + " :{[@|+]" + (channel) + " " + (space) + "}\r\n")
// are all replies
// generated in response to a WHOIS message.  Given that
// there are enough parameters present, the answering
// server must either formulate a reply out of the above
// numerics (if the query nick is found) or return an
// error reply.  The '*' in RPL_WHOISUSER is there as
// the literal character and not as a wild card.  For
// each reply set, only RPL_WHOISCHANNELS may appear
// more than once (for long lists of channel names).
// The '@' and '+' characters next to the channel name
// indicate whether a client is a channel operator or
// has been granted permission to speak on a moderated
// channel.  The RPL_ENDOFWHOIS reply is used to mark
// the end of processing a WHOIS message.


#define RPL_CHANNELMODEIS(channel, mode, modeParams) ("324 :" + (channel) + " " + (mode) + " " + (modeParams) + "\r\n")

#define RPL_NOTOPIC(channel) ("331 :" + (channel) + " :No topic is set\r\n")

#define RPL_TOPIC(channel, topic) ("332 :" + (channel) + " :" + (topic) + "\r\n")
// When sending a TOPIC message to determine the
// channel topic, one of two replies is sent.  If
// the topic is set, RPL_TOPIC is sent back else
// RPL_NOTOPIC.

#define RPL_INVITING(channel, nick) ("341 :" + (channel) + " " + (nick) + "\r\n")
// Returned by the server to indicate that the
// attempted INVITE message was successful and is
// being passed onto the end client.

#endif
