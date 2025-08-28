/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:49:31 by hsorel            #+#    #+#             */
/*   Updated: 2025/08/28 17:34:12 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"

vect2::vect2()
{
	this->_vec.push_back(0);
	this->_vec.push_back(0);
}

vect2::vect2(int v1, int v2)
{
	this->_vec.push_back(v1);
	this->_vec.push_back(v2);
}

vect2::vect2(const vect2 &other)
{
	//use the built-in vector assignement
	this->_vec = other._vec;
}

vect2::~vect2()
{

}


//minus
vect2 vect2::operator-()const
{
	vect2 res;
	res._vec[0] = this->_vec[0] * -1;
	res._vec[1] = this->_vec[1] * -1;
	return (res);
}

//index acssess
int &vect2::operator[](int i)
{
	if (i == 0 || i == 1)
		return (this->_vec[i]);
	//exception
	return (this->_vec[0]);
}

const int &vect2::operator[](int i)const
{
	if (i == 0 || i == 1)
		return (this->_vec[i]);
	//exception
	return (this->_vec[0]);
}

//increments/decrements

vect2 &vect2::operator++(void)
{
	this->_vec[0] += 1;
	this->_vec[1] += 1;
	return (*this);
}

vect2 &vect2::operator--(void)
{
	this->_vec[0] -= 1;
	this->_vec[1] -= 1;
	return (*this);
}
vect2 vect2::operator++(int)
{
	vect2 old(*this);
	this->_vec[0] += 1;
	this->_vec[1] += 1;
	return (old);	
}

vect2 vect2::operator--(int)
{
	vect2 old(*this);
	this->_vec[0] -= 1;
	this->_vec[1] -= 1;
	return (old);
}

//comparison
bool vect2::operator==(const vect2 &other)const
{
	return (this->_vec == other._vec);
}

bool vect2::operator!=(const vect2 &other)const
{
	return (this->_vec != other._vec);
}

//assignement

vect2 &vect2::operator=(const vect2 &other)
{
	if (this != &other)
	{
		this->_vec = other._vec;
	}
	return (*this);
}

vect2 &vect2::operator+=(const vect2 &other)
{
	this->_vec[0] += other._vec[0];
	this->_vec[1] += other._vec[1];
	return (*this);
}
vect2 &vect2::operator-=(const vect2 &other)
{
	this->_vec[0] -= other._vec[0];
	this->_vec[1] -= other._vec[1];
	return (*this);
}

vect2 &vect2::operator*=(const vect2 &other)
{
	this->_vec[0] *= other._vec[0];
	this->_vec[1] *= other._vec[1];
	return (*this);
}

vect2 &vect2::operator*=(int i)
{
	this->_vec[0] *= i;
	this->_vec[1] *= i;
	return (*this);
}

//vect2-vect2 operation

vect2 vect2::operator+(const vect2 &other)const
{
	vect2 res;
	res._vec[0] = this->_vec[0] + other._vec[0];
	res._vec[1] = this->_vec[1] + other._vec[1];
	return (res);
}

vect2 vect2::operator-(const vect2 &other)const
{
	vect2 res;
	res._vec[0] = this->_vec[0] - other._vec[0];
	res._vec[1] = this->_vec[1] - other._vec[1];
	return (res);
}

vect2 vect2::operator*(const vect2 &other)const
{
	vect2 res;
	res._vec[0] = this->_vec[0] * other._vec[0];
	res._vec[1] = this->_vec[1] * other._vec[1];
	return (res);
}

//vect2-int operation

vect2 vect2::operator+(int i)const
{
	vect2 res;
	res._vec[0] = this->_vec[0] + i;
	res._vec[1] = this->_vec[1] + i;
	return (res);
}

vect2 vect2::operator-(int i)const
{
	vect2 res;
	res._vec[0] = this->_vec[0] - i;
	res._vec[1] = this->_vec[1] - i;
	return (res);
}

vect2 vect2::operator*(int i)const
{
	vect2 res;
	res._vec[0] = this->_vec[0] * i;
	res._vec[1] = this->_vec[1] * i;
	return (res);
}

int vect2::getx()const
{
	return (this->_vec[0]);
}

int vect2::gety()const
{
	return (this->_vec[1]);
}

//cant use private vector so just use the ultiplication you used before
vect2 operator*(int scalar, const vect2 &v)
{
	return (v * scalar);
}

std::ostream &operator<<(std::ostream &out, const vect2 &v)
{
	out << v.getx() << ", " << v.gety() << std::endl;
	return (out);
}
