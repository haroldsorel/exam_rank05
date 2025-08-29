/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:48:51 by hsorel            #+#    #+#             */
/*   Updated: 2025/08/28 22:12:56 by hsorel           ###   ########.fr       */
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
       if (str.empty())
       {
	       this->_digits.push_back(0);
	       return ;
       }
       std::string::const_reverse_iterator it;
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

bigint::~bigint()
{

}

bigint &bigint::operator=(const bigint &other)
{
	if (this != &other)
	{
		this->_digits = other._digits;	
	}
	return (*this);
}

bigint &bigint::operator+=(const bigint &other)
{
	*this = *this + other;
	return (*this);
}

bigint &bigint::operator-=(const bigint &other)
{
	*this = *this - other;
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
	return (this->_digits == other._digits);
}

bool bigint::operator!=(const bigint &other)const
{

	return (this->_digits != other._digits);
}

bool bigint::operator<=(const bigint &other)const
{
	if (*this == other)
		return (true);
	if (*this < other)
		return (true);
	return (false);
}

bool bigint::operator>=(const bigint &other)const
{
	if (*this == other)
		return (true);
	if (*this > other)
		return (true);
	return (false);
}

bool bigint::operator<(const bigint &other)const
{
	if (this->_digits.size() < other._digits.size())
		return (true);
	if (this->_digits.size() > other._digits.size())
		return (false);
	if (*this == other)
		return (false);

	std::vector<int>::const_reverse_iterator rit1;
	std::vector<int>::const_reverse_iterator rit2;
	for (rit1 = this->_digits.rbegin(), rit2 = other._digits.rbegin(); rit1 != this->_digits.rend() && rit2 != other._digits.rend(); ++rit1, ++rit2)
	{
		if (*rit1 > *rit2)
			return (false);
	}
	return (true);
}

bool bigint::operator>(const bigint &other)const
{
	if (this->_digits.size() > other._digits.size())
		return (true);
	if (this->_digits.size() < other._digits.size())
		return (false);
	if (*this == other)
		return (false);
	
	std::vector<int>::const_reverse_iterator rit1;
	std::vector<int>::const_reverse_iterator rit2;
	for (rit1 = this->_digits.rbegin(), rit2 = other._digits.rbegin(); rit1 != this->_digits.rend() && rit2 != other._digits.rend(); ++rit1, ++rit2)
	{
		if (*rit1 < *rit2)
			return (false);
	}
	return (true);

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
	bigint max(*this);
	bigint min(other);
	
	if (max < min)
	{
		res = max;
		max = min;
		min = res;
		negativeRes = true;
	}

	res._digits.clear();
	for (size_t i = 0; i < max._digits.size(); i++)
	{
		diff = max._digits[i];
		if (borrow)
			diff -= 1;
		if (i < min._digits.size())
			diff -= min._digits[i];
		if (diff < 0)
		{
			diff += 10;
			borrow = true;
		}
		else
		{
			res._digits.push_back(diff);
			borrow = false;
		}
	}
	res._digits.push_back(diff);
	//there can be 0 before si handle that
	if (negativeRes)
		res._sign = -1;
	return (res);
}

bigint  bigint::operator<<(int shift)const
{
	if (shift <= 0)
		return (*this);

	//very important! if there is only one 0 you dont want to end up with 00000000
	if (this->_digits.size() == 1 && this->_digits[0] == 0)
		return (*this);

	bigint res(*this);
	for (int i = 0; i < shift; i++)
		res._digits.insert(res._digits.begin(), 0);
	return (res);
}

bigint bigint::operator>>(int shift)const
{
	bigint res;
	if (shift <= 0)
		return (*this);
	if (this->_digits.size() == 1 && this->_digits[0] == 0)
		return (*this);
	if (static_cast<size_t>(shift) >= this->_digits.size())
		return (res);
	res = *this;
	res._digits.erase(res._digits.begin(), res._digits.begin() + shift);
	return (res);
}

std::ostream &operator<<(std::ostream &out, const bigint &bi)
{
	std::vector<int>::const_reverse_iterator  rit;

	for (rit = bi._digits.rbegin(); rit != bi._digits.rend(); ++rit)
		out << *rit;
	return (out);
}

