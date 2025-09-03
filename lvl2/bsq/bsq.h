/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:46:48 by hsorel            #+#    #+#             */
/*   Updated: 2025/09/03 19:13:22 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_bsq
{
	int	size;
	char	empty;
	char	obstacle;
	char	full;
	char**	map;
}	t_bsq;

#endif
