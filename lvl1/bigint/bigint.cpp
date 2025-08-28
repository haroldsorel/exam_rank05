/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:48:51 by hsorel            #+#    #+#             */
/*   Updated: 2025/08/28 22:04:14 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"

bigint::bigint()
{
	this->_sign = 1;
	this->_digits.push_back(0);
}

//stores the integer in a reverse order! easier for maths
bigint::bigint(int n)
{
	long l;

	l = n;

	if (l == 0)
	{
		this->_digits.push_back(0);
		return ;
	}
	while (l > 0)
	{
		this->_digits.push_back(l % 10);
		l = l / 10;
	}

}

bigint::bigint(const std::string& str)
{
       if (value.empty())
       {
	       this->_digits.push_back(0);
	       return ;
       }
       std::string::iterator it;
       //assumes there are only digits! no error check
       for (it = str.rbegin(); it != str.rend(); ++it)
       {
	       this->_digits.push_back(*it - '0');
       }
}

bigint::bigint(const bigint &other)
{
	this->_digits = other._digits;
}

~bigint::bigint()
{

}

bigint &bigint::operator=(const bigint &other)
{
	if (this != *other)
	{
		this->_digits = other._digits;	
	}
	return (*this);
}

bigint &bigint::operator+=(const bigint &other)
{
	*this = *this + other;
	return (*this)
}

bigint &bigint::operator-=(const bigint &other)
{
	*this = *this - other;
	return (*this)
}

bigint &bigint::operator*=(const bigint &other)
{
	*this = *this * other;
	return (*this)
}

bigint &bigint::operator/=(const bigint &other)
{
	*this = *this / other;
	return (*this);
}

bigint &bigint::operator<<=(int i)
{
	*this = *this << i;
	return (*this);
}

bigint &bigint::operator>>=(int i)
{
	*this = *this >> i;
	return (*this);
}

bigint bigint::operator++(int)
{
	bigint before(*this);
	this->_digits[0]++;
	return (before);
}

bigint bigint::operator--(int)
{
	bigint before(*this);
	this->_digits[0]--;
	return (before);
}

bigint &bigint::operator++(void)
{
	this->_digits[0]++;
	return (*this);
}

bigint &bigint::operator--(void)
{
	this->_digits[0]--;
	return (*this);
}

bool bigint::operator==(const bigint &other)const
{
	return ((*this - other) == 0);
}

bool bigint::operator!=(const bigint &other)const
{

	return ((*this - other) != 0);
}

bool bigint::operator<=(const bigint &other)const
{
	return ((*this - other) <= 0);
}

bool bigint::operator>=(const bigint &other)const
{
	return ((*this - other) >= 0);
}

bool bigint::operator<(const bigint &other)const
{

	return ((*this - other) < 0);
}

bool bigint::operator>(const bigint &other)const
{

	return ((*this - other) > 0);
}

//assumes the numbers are positive ToDo negatives
bigint bigint::operator+(const bigint &other)const
{
	bool	carry = false;
	int	sum = 0;
	bigint res;

	res._digits.clear();
	//iterate for at least the longest number
	size_t maxIter = std::max(this->_digits.size(), other._digits.size());
	//iterate untill we have iterated max times and we have noting to carry
	for (size_t i = 0; i < maxIter || carry; i++)
	{
		sum = 0;
		if (carry)
			sum += 1;
		if (i < this->_digits.size())
			sum += this->_digits[i];
		if (i < other._digits.size())
			sum += other._digits[i];
		if (sum >= 10)
			carry = true;
		else
			carry = false;
		res._digits.push_back(sum % 10);
	}
	return (res);
}

//assumes positive integers. ToDo negatives
bigint bigint::operator-(const bigint &other)const
{
	bool	borrow = false;
	int	diff = 0;
	bool	negativeRes = false;

	bigint res;
	bigint max;
	bigint min;

	max = *this; //temporary, use the biggest out of both of them using >
	min = other;

	res._digits.clear();
	for (size_t i = 0; i < max.size(); i++)
	{
		diff = bigger._digits[i];
		if (borrow)
			diff -= 1;
		if (i < other._digits.size())
			diff -= other._digits[i];
		if (diff < 0)
		{
			res._digits.push_back(10 - (-diff));
			borrow = true;
		}
		else
		{
			res._digits.push_back(diff);
			borrow = false;
		}
	}
	//there can be 0 before si handle that
	if (negativeRes)
		res._sign = -1;
	return (res);
}

bigint bigint::operator*(const bigint &other)const
{

}

bigint bigint::operator/(const bigint &other)const
{

}

bigint  bigint::operator<<(int i)const
{

}

bigint bigint::operator>>(int i)const
{

}

std::ostream &bigint::operator<<(std::ostream &out, const bigint &bi)
{
	std::string::iterator rit;

	for (rit = rbegin(); rit != rend(); ++rit)
		out << *rit;
	return (out);
}

