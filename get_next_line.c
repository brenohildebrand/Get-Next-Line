/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:54:50 by bhildebr          #+#    #+#             */
/*   Updated: 2023/08/28 10:54:50 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

# define TRUE 1
# define FALSE 0

char	*get_next_line(int fd)
{
	static char *all = NULL;
	static char	*line = NULL;
	static int	reached_end_of_file = FALSE;
	int			nread;
	int			pos;
	char		buffer[BUFFER_SIZE];

	if (all == NULL)
	{
		ft_assign_s(&all, ft_newstr());
		if (all == NULL)
			return (NULL);
	}

	if (line != NULL)
	{
		free(line);
		line = NULL;
	}

	if (ft_strlen(all) > 0)
	{
		pos = ft_strchr_i(all, '\n');
		if (reached_end_of_file == TRUE && pos == -1)
			pos = ft_strlen(all) - 1;
		if (pos != -1)
		{
			ft_assign_s(&line, ft_substr(all, 0, pos));
			ft_assign_s(&all, ft_substr(all, pos + 1, ft_strlen(all) - 1));
			return (line);
		}
	}

	nread = read(fd, buffer, BUFFER_SIZE);

	if (nread == -1)
	{
		free(all);
		all = NULL;
		free(line);
		line = NULL;
		return (NULL);
	}
	else if (nread == 0)
	{
		if (reached_end_of_file == TRUE)
		{
			free(all);
			all = NULL;
			free(line);
			line = NULL;
			return (NULL);
		}
		reached_end_of_file = TRUE;
	}
	else if (nread > 0)
	{
		char *aux;

		ft_assign_s(&aux, ft_substr(buffer, 0, nread - 1));
		ft_assign_s(&all, ft_strjoin(all, aux));
		free(aux);
		if (all == NULL)
			return (NULL);
	}
	return (get_next_line(fd));
} 

int	main(char argc, char *argv[])
{
	int		fd;
	int		count;
	char	*line;

	if (argc != 2)
	{
		printf("Two arguments are expected.\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("An error ocurred while opening the file.\n");
		return (0);
	}
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("line\t-\t%i\t-\t%s\n", count++, line);
	}
	printf("\n");
}