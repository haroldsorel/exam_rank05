/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:54:45 by hsorel            #+#    #+#             */
/*   Updated: 2025/08/28 17:29:17 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

class vect2
{
	private:

		std::vector<int> _vec;
	public:
		vect2();
		vect2(int a, int b);
		vect2(const vect2 &src);

		~vect2();
		
		//getters
		int getx()const;
		int gety()const;
		
		//sign for -v. returns a copy and doesnt modify anything
		vect2 operator-()const;
		
		//index
		//always returns a reference and takes a int for index
		int &operator[](int index); //non const because you can modify from outside
		const int &operator[](int index)const; //to be used with const objects and make the reference return const as wll so you cant modify it from inside and outside

		//increments/decrements
		//pre incrementing takes a void and returns the reference of the incremented object
		vect2 &operator++(void);
		vect2 &operator--(void);
		//post incrementing takes a dummy int and returns a copy of the old value while incrementing the actual object
		vect2 operator++(int);
		vect2 operator--(int);

		//equal/non equal;
		//returns a boolean, takes a const refrence of the object you are comparing to. nothing is modified so its a const method
		bool operator==(const vect2 &other)const;
		bool operator!=(const vect2 &other)const;

		//assignement
		//returns the reference of the oject to which you modified by addinr or substrating another
		vect2 &operator=(const vect2 &other);
		vect2 &operator+=(const vect2 &other);
		vect2 &operator-=(const vect2 &other);
		vect2 &operator*=(const vect2 &other);
		vect2 &operator*=(int i);

		//operation
		//returns a new object that is the result of the operation and leaves all the others intact const
		vect2 operator+(const vect2 &other)const;
		vect2 operator+(int i)const;
		vect2 operator-(const vect2 &other)const;
		vect2 operator-(int i)const;
		vect2 operator*(const vect2 &other)const;
		vect2 operator*(int i)const;
};

//the most syntax heavy. include <ostream> header
//you receive the equivalent of a fd reference called std::ostream out and the actual vect2 that you want to print
//you then return a reference to the std::ostream out

std::ostream &operator<<(std::ostream &out, const vect2 &v);
vect2 operator*(int scalar, const vect2 &v);
