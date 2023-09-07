/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:13:20 by bhildebr          #+#    #+#             */
/*   Updated: 2023/09/06 19:16:15 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	int		fd;
	int		count;
	char	*line;

	if (argc != 2)
	{
		printf("Two arguments are expected.\n");
		return (0);
	}
	fd = open(argv[1], O_RDWR);
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
		printf("line\t-\t%.2i\t-\t%s", count++, line);
		free(line);
	}
	printf("\n");
}
