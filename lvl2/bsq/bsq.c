/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:46:41 by hsorel            #+#    #+#             */
/*   Updated: 2025/09/03 20:32:33 by hsorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	parse_first_line(t_bsq *bsq, char *buffer)
{
	int i = 0;

	while (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\f' || buffer[i] == '\r' || buffer[i] == '\v')
			i++;
	if (buffer[i] == '\0' || buffer[i] < '1' || buffer[i] > '9')
		return (-1);
	//inserting number of lines
	bsq->size = buffer[i] - '0';
	i++;
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
	bsq->map = malloc(sizeof(char *) * bsq->size);
	if (bsq->map == NULL)
		return (-1);
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
	char	*buffer; //for get line parameter
	size_t	len = 0; //for get line parameter
	ssize_t	read = 0; //for get line return
	
	int	i = 0;
	int	j = 0;

	int	line_size = -1;

	//parse the first line
	read = getline(&buffer, &len, stream);
	if (read == -1 || parse_first_line(bsq, buffer) == -1)
		return (-1);

	//allocate memory for array of string
	if (init_map(bsq) == -1)
		return (-1);

	//looping through the map
	while ((read = getline(&buffer, &len, stream)) != -1 && (i < bsq->size))
	{
		//keep a sentinal value
		if (line_size == -1)
			line_size = ft_strlen(buffer);

		//checking if all lines are the same len
		if (line_size != ft_strlen(buffer))
			return (-1);
		
		//checking if it is a least 1
		if (line_size < 1)
			return (-1);

		//checking if there is a new line
		if (buffer[line_size - 1] != '\n')
			return (-1);

		//if yes. pop it out
		buffer[line_size - 1] = '\0';

		//check if all chars in the buffer are accepted
		j = 0;
		while (buffer[j])
		{
			if (buffer[j] != bsq->empty && buffer[j] != bsq->full && buffer[j] != bsq->obstacle)
				return (-1);
			j++;
		}

		//buffer is cleared time to strdup
		bsq->map[i] = ft_strdup(buffer);
		i++;
	}
	//checking this has occured at least once so i have proof that there is a line
	if (i != bsq->size - 1)
		return (-1);
	return (1);
}

//forget about brute force by trying to expand a square of size 1, then 2, ... until you hit an obstacle or edge
//trivial to understand but terribly inefficient.
void	insert_square(t_bsq *bsq)
{
	int	x = 0;
	int	y = 0;
	int	size = 0;
}

int main(int argc, char **argv)
{
	FILE	*stream;
	t_bsq	bsq;

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
		return (1);
	}
	print_bsq(&bsq);
	insert__square(&bsq);
	print_bsq(&bsq);
	return (0);
}
