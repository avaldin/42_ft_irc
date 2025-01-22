/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.define.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaldin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:23:27 by tmouche           #+#    #+#             */
/*   Updated: 2025/01/22 11:48:52 by avaldin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_DEFINE_HPP
# define REPLY_DEFINE_HPP

#define RPL_NONE
// 300 Dummy reply number. Not used.

#define RPL_WELCOME(target) (":IRC_serv 001 " + (target) + " :Welcome to the Internet Relay Network, " + (target))
// Message displayed to the client when he registered successfully

#define RPL_AWAY(target, nick, awayMessage) (":IRC_serv 301 " + (target) + " " + (nick) + " :" + (away message))

#define RPL_UNAWAY ":You are no longer marked as being away"

#define RPL_NOWAWAY ":You have been marked as being away"
// These replies are used with the AWAY command (if allowed).
// RPL_AWAY is sent to any client sending a PRIVMSG to a client which is away.
// RPL_AWAY is only sent by the server to which the client is connected. Replies
// RPL_UNAWAY and RPL_NOWAWAY are sent when the client removes and sets an AWAY message.

#define RPL_WHOISUSER(target, nick, user, host, realName) (":IRC_serv 311 " + (target) + " " + (nick) + " " + (user) + " " + (host) + " * :" + (realname))

#define RPL_WHOISSERVER(target, nick, server, serverInfo) (":IRC_serv 312 " + (target) + " " + (nick) + " " + (server) + " :" + (server info))

#define RPL_WHOISOPERATOR(target, nick) (":IRC_serv 313 " + (target) + " " + (nick) + " :is an IRC Operator")

//#define RPL_WHOISIDLE(nick, integer) (":IRC_serv 317 " + (target) + " " + (nick) + " <idle_time> <signon_time> :seconds idle, signon time")

//#define RPL_ENDOFWHOIS(nick) (":IRC_serv 318 " + (target) + " <mask> :End of /WHOIS list.")


#define RPL_WHOISCHANNELS(target, nick, channel) (":IRC_serv 319 " + (target) + " " + (nick) + " :" + (channels))
//Info:
//This is returned when using the WHOIS command
//		<channels> is a space seperated list of one or more channels channels are listed from newest to oldest as received by the server (joined by the user or bursted) in that order each channel is formatted as [-][!][@|+|<]<channel>
//
//@ (+) means the user is opped (voiced) on the channel
//		< means the user is hidden on the channel (chanmode +D/+d)
//! for zombie
//
//
//		In ircu, if a user is kicked from the channel and the channel didn't become empty because of it, and the kick didn't come from the direction of the target's server, the user appears removed to other users, but internally the user stays in the channel as "zombie". It is then really removed when the "acknowledgement" PART is received. One reason for this is so mode changes done by the kick target just before he got kicked can apply because the server knows the user was in the channel with ops.
//
//Taken from 'the "beware" P10 protocol definition' http://ircd.bircd.org/bewarep10.html
//
//if the user has set usermode +d (deafmode) a '-' appears in front of all channels
//
//Example:
//irc.quakenet.org 319 Dana Dana :@#chan1 +#chan2 #chan3 <#chan4 !#chan5 !@#chan6
//		irc.quakenet.org 319 Dana Dana :-@#chan1 -+#chan2 -#chan3 -<#chan4 -!#chan5 -!@#chan6



#define RPL_CHANNELMODEIS(target, channel, mode) (":IRC_serv 324 " + (target) + " " + (channel) + " +" + (mode))

#define RPL_NOTOPIC(target, channel) (":IRC_serv 331 " + (target) + " " + (channel) + " :No topic is set.")

#define RPL_TOPIC(target, channel, topic) (":IRC_serv 332 " + (target) + " " + (channel) + " :" + (topic))
// When sending a TOPIC message to determine the
// channel topic, one of two replies is sent.  If
// the topic is set, RPL_TOPIC is sent back else
// RPL_NOTOPIC.

#define RPL_INVITING(target, channel, nick) (":IRC_serv 341 " + (target) + " " + (nick) + " " + (channel))
// Returned by the server to indicate that the
// attempted INVITE message was successful and is
// being passed onto the end client.

#define RPL_NAMERPLY(target, channel, names) (":IRC_serv 353 " + (target) + " = " + (channel) + " :" + (names))
#define RPL_ENDOFNAMES(target, channel) (":IRC_serv 366 " + (target) + " " + (channel) + " :End of NAMES list")

#endif
