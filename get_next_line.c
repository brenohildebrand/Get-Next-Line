/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:11:20 by bhildebr          #+#    #+#             */
/*   Updated: 2023/08/05 16:23:28 by bhildebr         ###   ########.fr       */
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
	return (c);
}

char	*get_next_line(int fd)
{
	static char	*line = 0;
	int			char_number;
	char		c;

	free(line);
	line = malloc(sizeof(char));
	char_number = 0;	
	while (1)
	{
		c = get_next_char(fd);
		if (c == 0)
		{
			line[char_number] = 0;
			break ;
		}
		line[char_number] = c;
		if (line[char_number] == '\n')
			break ;
		char_number++;
		if (char_number == sizeof(line))
		if (char_number == sizeof(line))
			line = realloc(line, sizeof(line) + 1);
	}
	return (line);
}