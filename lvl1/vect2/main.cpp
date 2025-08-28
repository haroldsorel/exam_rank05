/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:54:29 by hsorel            #+#    #+#             */
/*   Updated: 2025/08/28 17:12:57 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"

int main()
{
	vect2 v1;
	vect2 v2(1,2);
	const vect2 v3(v2);
	vect2 v4 = v2;
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v1: " << "{" << v1[0] << ", " << v1[1] << "}" << std::endl;
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "v3: " << v3 << std::endl;
	std::cout << "v4: " << v4 << std::endl;
	std::cout << v4++ << std::endl;
	std::cout << ++v4 << std::endl;
	std::cout << v4-- << std::endl;
	std::cout << v2 * 3 << std::endl;
	v2+=v3;
	v1-=v2;
	v2 = v3 + v3 * 2;
	std::cout << "v2 = " << v2 << std::endl;
	v2 = 3 * v2;
	std::cout << "v2 = " << v2 << std::endl;
	v2 += v2 += v3;
	v1 *= 42;
	v1 = v1-v1+v1;
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v2 = " << v2 << std::endl;
	std::cout << "-v2: " << -v2 << std::endl;
	std::cout << "v1[1]: " << v1[1] << std::endl;
	v1[1] = 12;
	std::cout << "v1[1]: " << v1[1] << std::endl;
	std::cout << "v3[1]: " << v3[1] << std::endl;
	std::cout << "v1 == v3: " << (v1 == v3) << std::endl;
	std::cout << "v1 == v1: " << (v1 == v1) << std::endl;
	std::cout << "v1 != v3: " << (v1 != v3) << std::endl;
	std::cout << "v1 != v1: " << (v1 != v1) << std::endl;
}
