/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operator.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:07:34 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/29 17:14:16 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_CLASS_HPP
# define OPERATOR_CLASS_HPP
# include "Client.class.hpp"

class Operator : public Client {
public:
	Operator( void );
	~Operator( void );
	Operator(Operator const & src);
	
	Operator&	operator=(Operator const & rhs);

private:
};

#endif
