/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:46:41 by hsorel            #+#    #+#             */
/*   Updated: 2025/09/03 23:21:13 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	parse_first_line(t_bsq *bsq, char *buffer)
{
	int i = 0;

	while (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\f' || buffer[i] == '\r' || buffer[i] == '\v')
			i++;
	while (buffer[i] != '\0' && buffer[i] >= '0' && buffer[i] <= '9')
	{
			bsq->size = bsq->size * 10 + (buffer[i] - '0');
			i++;
	}
	if (bsq->size == 0 && buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != '\f' && buffer[i] != '\r' && buffer[i] != '\v')
		return (-1);
	//inserting number of lines
	while (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\f' || buffer[i] == '\r' || buffer[i] == '\v')
		i++;
	if (buffer[i] == '\0')
		return (-1);
	//inserting empty char
	bsq->empty = buffer[i];
	i++;
	while (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\f' || buffer[i] == '\r' || buffer[i] == '\v')
		i++;
	if (buffer[i] == '\0')
		return (-1);
	//inserting obstacle char
	bsq->obstacle = buffer[i];
	i++;
	while (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\f' || buffer[i] == '\r' || buffer[i] == '\v')
		i++;
	if (buffer[i] == '\0')
		return (-1);
	//inserting full char
	bsq->full = buffer[i];
	i++;
	while (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\f' || buffer[i] == '\r' || buffer[i] == '\v')
		i++;
	//checking that there is nothing else in the line and that there is something after (not a backslash 0)
	if (buffer[i] != '\n')
		return (-1);
	//checking that there isn't two same values
	if (bsq->empty == bsq->obstacle || bsq->empty == bsq->full || bsq->obstacle == bsq->full)
		return (-1);
	return (1);
}

int	init_map(t_bsq *bsq)
{
	int i = 0;
	bsq->map = malloc(sizeof(char *) * bsq->size);
	if (bsq->map == NULL)
		return (-1);
	while (i < bsq->size)
	{
		bsq->map[i] = NULL;
		i++;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char *copy;
	int size;
	int i = 0;

	size = ft_strlen(str);

	copy = malloc(sizeof(char) * (size + 1));
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);

}

void	print_bsq(t_bsq *bsq)
{
	int	i = 0;

	while (i < bsq->size)
	{
		fprintf(stdout, "%s\n", bsq->map[i]);
		i++;
	}
}

int parse_file(t_bsq *bsq, FILE *stream)
{
	char	*buffer = NULL; //for get line parameter
	size_t	len = 0; //for get line parameter
	ssize_t	read = 0; //for get line return
	
	int	i = 0;
	int	j = 0;

	int	line_size = -1;

	//parse the first line
	read = getline(&buffer, &len, stream);
	if (read == -1 || parse_first_line(bsq, buffer) == -1)
		return (free(buffer), -1);

	//allocate memory for array of string
	if (init_map(bsq) == -1)
		return (free(buffer), -1);

	//looping through the map
	while ((read = getline(&buffer, &len, stream)) != -1 && (i < bsq->size))
	{
		//keep a sentinal value
		if (line_size == -1)
			line_size = ft_strlen(buffer);

		//checking if all lines are the same len
		if (line_size != ft_strlen(buffer))
			return (free(buffer), -1);
		
		//checking if it is a least 1
		if (line_size < 1)
			return (free(buffer), -1);

		//checking if there is a new line
		if (buffer[line_size - 1] != '\n')
			return (free(buffer), -1);

		//if yes. pop it out
		buffer[line_size - 1] = '\0';

		//check if all chars in the buffer are accepted
		j = 0;
		while (buffer[j])
		{
			if (buffer[j] != bsq->empty && buffer[j] != bsq->full && buffer[j] != bsq->obstacle)
				return (free(buffer), -1);
			j++;
		}

		//buffer is cleared time to strdup
		bsq->map[i] = ft_strdup(buffer);
		i++;
	}
	free(buffer);
	//checking this has occured at least once so i have proof that there is a line
	if (i < bsq->size)
		return (-1);
	bsq->len = line_size - 1;
	return (1);
}


int	min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= a && b <= c)
		return (b);
	if (c <= a && c <= b)
		return (c);
	return (90);
}

void	free_bsq(t_bsq *bsq)
{
	int i = 0;

	if (bsq->map == NULL)
		return ;
	while (i < bsq->size)
	{
		if (bsq->map[i] != NULL)
			free(bsq->map[i]);
		i++;
	}
	free(bsq->map);
	bsq->map = NULL;
}

void	free_array_int(int **arr, int col)
{
	int i = 0;

	while (i < col)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	find(t_bsq *bsq)
{
	int	col = 0;
	int	row = 0;

	int	padded_size = bsq->size + 1;
	int	padded_len = bsq->len + 1;

	//creating padded matrix
	int **padded = malloc(sizeof(int *) * (padded_size));
	while (col < padded_size)
	{
		padded[col] = malloc(sizeof(int) * (padded_len));
		col++;
	}

	//filling up with zeroes
	col = 0;
	while (col < padded_size)
	{
		row = 0;
		while (row < padded_len)
		{
			padded[col][row] = 0;
			row++;
		}
		col++;
	}

	//filling up the data. offset the padding
	col = 1;
	row = 1;

	while (col < padded_size)
	{
		row = 1;
		while (row < padded_len)
		{
			//offset to  match the actual map
			if (bsq->map[col - 1][row - 1] == bsq->obstacle)
				padded[col][row] = 0;
			else
			{
				padded[col][row] = min(padded[col - 1][row], padded[col][row - 1], padded[col - 1][row - 1]) + 1;
			}
			row++;
		}
		col++;
	}

	//getting the first biggest square
	col = 1;
	row = 1;
	int	max = 0;
	int	col_max = col;
	int	row_max = row;
	while (col < padded_size)
	{
		row = 1;
		while (row < padded_len)
		{
			if (padded[col][row] > max)
			{
				max = padded[col][row];
				col_max = col;
				row_max = row;
			}
			row++;
		}
		col++;
	}
	//now max is the size of our biggest first square and col_max and row_max are dowm right corner
	//we can free the padded
	free_array_int(padded, padded_size);


	//offsetting the index to match bsq
	col_max--;
	row_max--;
	col = col_max;
	row = row_max;
	
	//if it was only obstacles
	if (max == 0)
		return ;
	
	//inserting the square in the map
	while (col > col_max - max)
	{
		row = row_max;
		while(row > row_max - max)
		{
			bsq->map[col][row] = bsq->full;
			row--;
		}
		col--;
	}

}

int main(int argc, char **argv)
{
	FILE	*stream;
	t_bsq	bsq;

	bsq.map = NULL;
	bsq.size = 0;

	//check that there is an input
	if (argc != 2)
	{
		fprintf(stderr, "No file\n");
		return (1);
	}
	stream = fopen(argv[1], "r");
	//check that the file opened correctly
	if (stream == NULL)
	{
		fprintf(stderr, "Open Failure\n");
		return (1);
	}
	if (parse_file(&bsq, stream) == -1)
	{
		fprintf(stderr, "Map Error");
		fclose(stream);
		free_bsq(&bsq);
		return (1);
	}
	fclose(stream);
	print_bsq(&bsq);
	find(&bsq);
	print_bsq(&bsq);
	free_bsq(&bsq);
	return (0);
}
