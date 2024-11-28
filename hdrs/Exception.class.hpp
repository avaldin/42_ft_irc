/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:58:10 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/28 20:14:43 by tmouche          ###   ########.fr       */
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

class ServerStartException : public Exception {
	public:
		void	what() const throw() {
			std::cerr << "Error: Server already started" << std::endl;
		}
};

class EpollCreateException : public Exception {
	public:
		void	what() const throw() {
			std::cerr << "Error: Epoll create failed" << std::endl;
		}
};

class EpollCtlException : public Exception {
	public:
		void	what() const throw() {
			std::cerr << "Error: Epoll ctl failed" << std::endl;
		}
};

class EpollWaitException : public Exception {
	public:
		void	what() const throw() {
			std::cerr << "Error: Epoll wait failed" << std::endl;
		}
};

class OpenException : public Exception {
	public:
		void	what() const throw() {
			std::cerr << "Error: Open failed" << std::endl;
		}	
};

class IfstreamException : public Exception {
	public:
		void	what() const throw() {
			std::cerr << "Error: Ifstream failed" << std::endl;
		}
};

#endif
