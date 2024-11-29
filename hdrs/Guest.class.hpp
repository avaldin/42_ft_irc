/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Guest.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmouche <tmouche@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:31:30 by tmouche           #+#    #+#             */
/*   Updated: 2024/11/29 20:01:26 by tmouche          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUEST_CLASS_HPP
# define GUEST_CLASS_HPP
# include "Client.class.hpp"

class Guest : public Client {
public:
	Guest( void );
	virtual ~Guest( void );
	Guest(Guest const & src);
	
	Guest&	operator=(Guest const & rhs);

private:
};

#endif