/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 22:29:35 by bhildebr          #+#    #+#             */
/*   Updated: 2023/08/15 22:29:35 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int		fd;
	int		line_number;
	char	*line;

	line_number = 1;
	if (argc < 2)
	{
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("FD ERROR!\n");
		return (0);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%2i: %s", line_number++, line);
	}
	printf("\n");
	return (0);
}