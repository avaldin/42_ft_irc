/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BotError.define.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaud <thibaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 03:26:49 by thibaud           #+#    #+#             */
/*   Updated: 2025/01/24 05:36:57 by thibaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOTERROR_DEFINE_HPP
# define BOTERROR_DEFINE_HPP

#define BOTERR_NEEDMOREPARAMS(command) ((command) + " :Not enough parameters")

#define BOTERR_USERNOTVALID(target) ((target) + " :Not a valid target")

#define BOTERR_DUELNOTVALID " :Duel is not valid for several reasons"

#define BOTERR_NOTAPLAYER(target) ((target) + " :Not a player")

#define BOTERR_NOTINDUEL(client) ((client) + " :Not in a duel")

#define BOTERR_DUELHIMSELF(client) ((client) + " :Can not duel himself")

#endif