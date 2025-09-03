/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:42:21 by haroldsorel       #+#    #+#             */
/*   Updated: 2025/09/03 01:40:26 by haroldsorel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>


//so either here you do a 2 dimension array to represent the board
//or you just put everything in a string if you go down it is +height

typedef struct s_board
{
	int	width;
	int	height;
	char 	**board;
} t_board;

#endif
