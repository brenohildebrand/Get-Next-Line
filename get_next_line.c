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

char	*get_next_line(int fd)
{
	char	buffer[BUFFER_SIZE];
	int		is_line_complete;
	int		i;
	int		did_you_read;
	static char	*line = NULL;
	static char *tail = NULL;
	static int	all_read = NULL;

	// verify if there's a line on tail
	// read BUFFER_SIZE and append to tail
	// call gnl again

	

	//
	//
	//
	//

	did_you_read = read(fd, buffer, BUFFER_SIZE);
	if (did_you_read < BUFFER_SIZE)
	{
		line = ft_strjoin(tail, ft_substr(buffer, 0, did_you_read - 1)); // substr must return NULL in (buffer, 0, -1)
		tail = NULL;
		return (line);
	}

	i = 0;
	while (i < BUFFER_SIZE - 1 && buffer[i] != '\n')
		i++;

	is_line_complete = (buffer[i] == '\n');
	

	if (is_line_complete)
	{
		line = ft_strjoin(tail, ft_substr(buffer, 0, i));
		tail = ft_strjoin(tail, ft_substr(buffer, i + 1, BUFFER_SIZE - 1));
		return (line);
	}
	else
	{
		tail = ft_strjoin(tail, buffer);
		return (get_next_line(fd));
	}

	// read BUFFER_SIZE to buffer
	// get line
	// keep the tail
	// return line
	// read next
	// OBS: free memory
	nread = read(fd, buffer, BUFFER_SIZE);
}

int	main(char argc, char *argv[])
{
	int		fd;
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
	while (1)
	{
		line = get_next_line(fd);
		if (line == (void *)0)
			break ;
		printf("%s", get_next_line(fd));
	}
	printf("\n");
}