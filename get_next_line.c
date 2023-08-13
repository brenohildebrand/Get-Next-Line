/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:11:20 by bhildebr          #+#    #+#             */
/*   Updated: 2023/08/13 17:08:05 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char	get_next_char(int fd)
{
	char		c;
	int			result;

	result = read(fd, &c, 1);
	if (result == -1)
		return (0);
	if (result == 0)
		return (0);
	return (c);
}

char	*get_next_line(int fd)
{
	static char	*line = 0;
	int			i;
	char		c;
	
	free(line);
	line = malloc(sizeof(char));
	i = 0;	
	while (1)
	{
		c = get_next_char(fd);
		if (c == 0)
		{
			line[i] = 0;
			if (i > 1)
				break ;
			else
			{
				free(line);
				return (NULL);
			}
		}
		line[i] = c;
		if (line[i] == '\n')
		{
			line[i] = '\n';
			break ;
		}
		i++;
		if (i == sizeof(line))
			line = ft_realloc(line, sizeof(line) + 1);
	}
	return (line);
}