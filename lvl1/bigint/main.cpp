/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 01:46:27 by haroldsorel       #+#    #+#             */
/*   Updated: 2025/08/29 01:46:28 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"
int main()
{
    const bigint a(42);
    bigint b(21548), c, d(1337), e(d);
    std::cout << (b >> 4) << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "(c+= a) = " << (c += a) << std::endl;
    //std::cout << "c - a = " << c - a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "++b = " << ++b << std::endl;
    std::cout << "b++ = " << b++ << std::endl;
    std::cout << "(b << 10) + 42 = " <<  (b << 10) + 42 << std::endl;
    std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
    std::cout << "(d >>= 2) = " << (d >>= 2) << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "d = " << d << std::endl;
    bigint f("42");
    std::cout << "f = " << f << std::endl;
    std::cout << "a == f = " << (a == f) << std::endl;
    std::cout << "a <= f = " << (a <= f) << std::endl;
    std::cout << "a >= f = " << (a >= f) << std::endl;
    std::cout << "a < f = " << (a < f) << std::endl;
    std::cout << "a > f = " << (a > f) << std::endl;
    std::cout << "(d < a) = " << (d < a) << std::endl;
    std::cout << "(d > a) = " << (d > a) << std::endl;
    std::cout << "(d == a) = " << (d == a) << std::endl;
    std::cout << "(d != a) = " << (d != a) << std::endl;
    std::cout << "(d <= a) = " << (d <= a) << std::endl;
    std::cout << "(d >= a) = " << (d >= a) << std::endl;
}