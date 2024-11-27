/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:58:10 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/27 20:40:00 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTION_CLASS_HPP
# define EXCEPTION_CLASS_HPP
# include <iostream>

class Exception {
	public:
		virtual void	what() const throw() = 0;
};

class SocketException : public Exception {
	public:
		void	what() const throw() {
			std::cerr << "Error: Socket failed" << std::endl;
		}
};

class BindException : public Exception {
	public:
		void	what() const throw() {
			std::cerr << "Error: Bind failed" << std::endl;
		}
};

class ListenException : public Exception {
	public:
		void	what() const throw() {
			std::cerr << "Error: Listen failed" << std::endl;
		}
};

class AcceptException : public Exception {
	public:
		void	what() const throw() {
			std::cerr << "Error: Accept failed" << std::endl;
		}
};

#endif
