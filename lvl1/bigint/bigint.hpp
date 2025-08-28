/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:02:26 by hsorel            #+#    #+#             */
/*   Updated: 2025/08/28 20:15:12 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <ostream>
#include <vector>

class bigint
{
	private:
		std::vector<int> digits;
	public:
		//constructors
		bigint();
		bigint(int n);
		bigint(const std::string &str);
		bigint(const bigint &other);
		//deconstructor
		~bigint();
		//assignement
		//return value : reference to itself
		//parameters : another const bigint
		//const? no. object changes
		bigint &operator=(const bigint &other);
		bigint &operator+=(const bigint &other);
		bigint &operator-=(const bigint &other);
		bigint &operator*=(const bigint &other);
		bigint &operator/=(const bigint &other);
		bigint &operator<<=(int i); //bitshifting: Multiplies the number by 2^i
		bigint &operator>>=(int i); //bitshifting: Divides the number by 2^i
		//post increment
		//return value : copy of old value
		//parameter : int (dummy value)
		//const? no. object changes
		bigint operator++(int);
		bigint operator--(int);
		//pre increment
		//return value : reference to itself
		//parameter : void (dummy value)
		bigint &operator++(void);
		bigint &operator--(void);
		//comparison
		//return value : boolean
		//parameter : another const bigint
		//const? yes. no changes to object
		bool operator==(const bigint &other)const;
		bool operator!=(const bigint &other)const;
		bool operator<=(const bigint &other)const;
		bool operator>=(const bigint &other)const;
		bool operator<(const bigint &other)const;
		bool operator>(const bigint &other)const;
		//operations
		//return value : copy of the result of the operation
		//parameter : type of right side operand
		//const? yes. no changes, only copy
		bigint operator+(const bigint &other)const;
		bigint operator-(const bigint &other)const;
		bigint operator*(const bigint &other)const;
		bigint operator/(const bigint &other)const;
		bigint operator<<(int i)const; //bitshifting: Multiplies the number by 2^i
		bigint operator>>(int i)const; //bitshifting: Divides the number by 2^i
};

//if you want access to private attributes but it in the class and put the keyword friends before
std::ostream &operator<<(std::ostream &out, const bigint &bi);










