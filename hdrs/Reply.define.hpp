/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.define.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:23:27 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/29 15:31:06 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_DEFINE_HPP
# define REPLY_DEFINE_HPP

#define RPL_NONE
// 300 Dummy reply number. Not used.

#define RPL_AWAY(nick, awayMessage) nick" :"awayMessage
// 301

#define RPL_UNAWAY ":You are no longer marked as being away"
// 305

#define RPL_NOWAWAY ":You have been marked as being away"
// 306 - 305 These replies are used with the AWAY command (if allowed).
// RPL_AWAY is sent to any client sending a PRIVMSG to a client which is away.
// RPL_AWAY is only sent by the server to which the client is connected. Replies
// RPL_UNAWAY and RPL_NOWAWAY are sent when the client removes and sets an AWAY message.

#define RPL_WHOISUSER(nick, user, host, realName) nick" "user" "host" * :"realName
// 311

#define RPL_WHOISSERVER(nick, server, serverInfo) nick" "server" "serverInfo
// 312

#define RPL_WHOISOPERATOR(nick) nick": is an IRC operator"
// 313

#define RPL_WHOISIDLE(nick, integer) nick" "integer" :seconds idle"
// 317

#define RPL_ENDOFWHOIS(nick) nick" :End of /WHOIS list"
// 318

#define RPL_WHOISCHANNELS(nick, channel, space) nick " :{[@|+]"channel" "space"}"
// 319 Replies 311 - 313, 317 - 319 are all replies
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


#define RPL_CHANNELMODEIS(channel, mode, modeParams) channel" "mode" "modeParams
// 324

#define RPL_NOTOPIC(channel) channel" :No topic is set"
// 331

#define RPL_TOPIC(channel, topic) channel" :"topic
// 332 When sending a TOPIC message to determine the
// channel topic, one of two replies is sent.  If
// the topic is set, RPL_TOPIC is sent back else
// RPL_NOTOPIC.

#define RPL_INVITING(channel, nick) channel" "nick
// 341 Returned by the server to indicate that the
// attempted INVITE message was successful and is
// being passed onto the end client.

#endif
