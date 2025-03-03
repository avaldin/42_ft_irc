/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DuelbotParser.class.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:30:56 by thibaud           #+#    #+#             */
/*   Updated: 2025/01/24 19:36:28 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DUELBOTPARSER_CLASS_HPP
# define DUELBOTPARSER_CLASS_HPP
# include <string>
# include <vector>
# include <map>

class CommandBot;

class DuelbotParser {
public:
	~DuelbotParser( void ) {}
	DuelbotParser(std::string const & rawline);

	CommandBot*	getCommand( void );

	std::string	cmdName;
	std::string	botName;
private:
	void	parseRawline( void );

	void	setDuel(std::vector<std::string> splitedLine, int idx);
	void 	setRank(std::vector<std::string> splitedLine, int idx);
	void	setAccept(std::vector<std::string> splitedLine, int idx);
	void	setRefuse(std::vector<std::string> splitedLine, int idx);
	void	setScoreboard(std::vector<std::string> splitedLine, int idx);

	CommandBot*	_command;
	std::string	_rawline;

	std::map<std::string,void(DuelbotParser::*)(std::vector<std::string>, int)>	_cmdMethods;
	
};

#endif
