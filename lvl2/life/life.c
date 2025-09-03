/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haroldsorel <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 23:51:29 by haroldsorel       #+#    #+#             */
/*   Updated: 2025/09/03 14:28:19 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	print_board(t_board board)
{
	int	col = 0;
	int	line = 0;

	while (col < board.height)
	{
		line = 0;
		while (line < board.width)
		{
			putchar(board.board[col][line]);
			line++;
		}
		col++;
		putchar('\n');
	}
}

void	free_copy(char **copy, t_board *board);

char**	copy_board(t_board *board)
{
	int	col = 0;
	int	line = 0;

	char **copy = malloc(board->height * sizeof(char *));
	if (copy == NULL)
		return (NULL);
	while (col < board->height)
	{
		line = 0;
		copy[col] = malloc(board->width * (sizeof(char)));
		if (copy[col] == NULL)
		{
			free_copy(copy, board);
			return (NULL);
		}
		while (line < board->width)
		{
			copy[col][line] = board->board[col][line];
			line++;
		}
		col++;
	}
	return (copy);
}

void	free_copy(char **copy, t_board *board)
{
	int	col = 0;

	while (col < board->height)
	{
		if (copy[col] != NULL)
			free(copy[col]);
		col++;
	}
	free(copy);
}

void	free_board(t_board *board)
{
	int	col = 0;

	if (board->board == NULL)
		return ;
	while (col < board->height)
	{
		if (board->board[col] != NULL)
			free(board->board[col]);
		col++;
	}
	free(board->board);
}

int	init_board(t_board *board, char **argv)
{
	int	col = 0;
	int	line = 0;

	board->width = atoi(argv[0]);
	board->height = atoi(argv[1]);

	board->board = malloc(board->height * sizeof(char *));
	if (board->board == NULL)
		return (-1);
	while (col < board->height)
	{
		line = 0;
		board->board[col] = malloc(board->width * (sizeof(char)));
		if (board->board[col] == NULL)
		{
			free_board(board);
			return (-1);
		}
		while (line < board->width)
		{
			board->board[col][line] = ' ';
			line++;
		}
		col++;
	}
	return (1);
}

int	draw_life(t_board *board)
{
	char	buffer;
	int	ret;
	int	col = 0;
	int	line = 0;
	int	pen_down = 0;

	//read function will loop until EOF is found (when read returns 0)
	// REMEMBER READ(FD, BUFFER, SIZE) returns 1 on success, 0 on EOF and -1 on error
	while ((ret = read(0, &buffer, 1)) == 1)
	{
		if (buffer == 'w')
		{
			if (col == 0)
			{
				ret = -1;
				break;
			}
			col--;
		}
		else if (buffer == 'a')
		{
			if (line == 0)
			{
				ret = -1;
				break;
			}
			line--;
		}
		else if (buffer == 's')
		{
			if (col == board->height - 1)
			{
				ret = -1;
				break;
			}
			col++;
		}
		else if (buffer == 'd')
		{
			if (line == board->width - 1)
			{
				ret = -1;
				break;
			}
			line++;
		}
		else if (buffer == 'x')
		{
			if (pen_down == 0)
				pen_down = 1;
			else
			{
				pen_down = 0;
			}
		}
		//what should i do when they try some shit inside?
		//what if they are using echo and there is a /n?
		//should i skip whitespaces? trim the beginning or the end?
		//else
		//{
		//	ret = -1;
		//	break;
		//}
		if (pen_down == 1)
			board->board[col][line] = '0';
	}
	if (ret == -1)
	{
		free_board(board);
		return (-1);
	}
	return (1);
}

void	alive_life(t_board *board, char **copy)
{
	int	col = 0;
	int	line = 0;
	int	friends = 0;
	int	alive = 0;

	//Here you have to make a copy of the board so you keep the initial state
	while (col < board->height)
	{
		line = 0;
		while (line < board->width)
		{
			alive = 0;
			friends = 0;
			if (copy[col][line] == '0')
				alive = 1;

			//border checking and friends incrementing
			if (col != 0 && copy[col - 1][line] == '0')
				friends++;
			if (col != 0 && line != 0 && copy[col - 1][line - 1] == '0')
				friends++;
			if (col != 0 && line != board->width - 1 && copy[col - 1][line + 1] == '0')
				friends++;
			if (col != board->height - 1 && copy[col + 1][line] == '0')
				friends++;
			if (col != board->height - 1 && line != 0 && copy[col + 1][line - 1] == '0')
				friends++;
			if (col != board->height - 1 && line != board->width - 1 && copy[col + 1][line + 1] == '0')
				friends++;
			if (line != 0 && copy[col][line - 1] == '0')
				friends++;
			if (line != board->width - 1 && copy[col][line + 1] == '0')
				friends++;

			//checking if the element has to be alived
			
			if (alive == 1 && friends < 2)
				board->board[col][line]	= ' ';
			else if (alive == 1 && (friends == 2 || friends == 3))
				board->board[col][line]	= '0';
			else if (alive == 1 && friends > 3)
				board->board[col][line]	= ' ';
			else if (alive == 0 && friends == 3)
				board->board[col][line]	= '0';
			line++;
		}
		col++;
	}
}

int	loop_life(t_board *board, int iteration)
{
	int i = 0;
	char **copy;

	while (i < iteration)
	{
		copy = copy_board(board);
		if (copy == NULL)
		{
			free_board(board);
			return (-1);
		}
		alive_life(board, copy);
		i++;
		print_board(*board);
		sleep(1);
		free_copy(copy, board);
		putchar('\n');
	}
	return (1);
}

int	isnumber(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}


//what if we have a board of one or both dimensions 0?
int	input(char **argv)
{
	int i = 1;

	while (argv[i])
	{
		if (isnumber(argv[i]) == 0)
			return (-1);
		i++;
	}
	if (atoi(argv[1]) == 0 || atoi(argv[2]) == 0)
		return (-1);
	return (1);
}

void	ft_putstr(char *str)
{
	int i = 0;
	
	while (str[i])
	{
		putchar(str[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_board	board;

	if (argc != 4 ||input(argv) == -1)
	{
		ft_putstr("Wrong Input");
		return (1);
	}
	argv++;
	if (init_board(&board, argv) == -1)
	{
		ft_putstr("Init Failure");
		return (1);
	}
	if (draw_life(&board) == -1)
	{
		ft_putstr("Draw Failure");
		return (1);
	}
	print_board(board);
	sleep(1);
	putchar('\n');
	if (loop_life(&board, atoi(argv[2])) == -1)
	{
		ft_putstr("Loop Failure");
		return (1);
	}
	free_board(&board);
	return (0);
}













