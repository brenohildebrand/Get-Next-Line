/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:13:15 by bhildebr          #+#    #+#             */
/*   Updated: 2023/09/06 19:53:35 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_line_length(int _index, t_list *_list)
{
	int		length;

	length = 0;
	while (_list != NULL)
	{
		while (_index < BUFFER_SIZE)
		{
			if (_list->content[_index] == '\n')
			{
				length++;
				break ;
			}
			length++;
			_index++;
		}
		if (_index < BUFFER_SIZE)
			break ;
		else
		{
			_index = 0;
			_list = _list->next;
		}
	}
	return (length);
}

void	advance_to_next_node(t_gnl *d)
{
	t_list	*_list;

	_list = d->list;
	d->list = d->list->next;
	free(_list->content);
	free(_list);
	d->index = 0;
}

void	copy_from_list_to_line(t_gnl *d)
{
	int		line_index;

	line_index = 0;
	while (d->list != NULL)
	{
		while (d->index < BUFFER_SIZE)
		{
			(d->line)[line_index] = d->list->content[d->index];
			if (d->list->content[d->index] == '\n')
				break ;
			(d->index)++;
			line_index++;
		}
		if (d->index < BUFFER_SIZE)
		{
			(d->index)++;
			if (d->index == BUFFER_SIZE || d->list->content[d->index] == '\0')
				advance_to_next_node(d);
			line_index++;
			break ;
		}
		else
			advance_to_next_node(d);
	}
	d->line[line_index] = '\0';
}

int	get_line_from_list(t_gnl *d)
{
	int	length;

	if (d->nlines > 0)
	{
		length = get_line_length(d->index, d->list);
		d->line = malloc((length + 1) * sizeof(char));
		if (d->line == NULL)
			return (-1);
		copy_from_list_to_line(d);
		(d->nlines)--;
		return (0);
	}
	else
	{
		return (0);
	}
}

char	*get_next_line(int fd)
{
	static t_gnl	data = {
		.list = NULL,
		.nlines = 0,
		.index = 0,
	};

	data.line = NULL;
	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, NULL, 0))
		return (NULL);
	if (get_line_from_list(&data) == -1)
		return (NULL);
	if (data.line)
		return (data.line);
	if (read_from_file_to_list(fd, &data) == -1)
		return (NULL);
	if (get_line_from_list(&data) == -1)
		return (NULL);
	if (data.line)
		return (data.line);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:13:20 by bhildebr          #+#    #+#             */
/*   Updated: 2023/09/06 16:11:07 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// // #include "get_next_line.h"

// #include <fcntl.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int	main(int argc, char *argv[])
// {
// 	int		fd;
// 	int		count;
// 	char	*line;

// 	fd = open("test03.txt", O_RDWR);
// 	if (fd == -1)
// 	{
// 		printf("An error ocurred while opening the file.\n");
// 		return (0);
// 	}
// 	count = 0;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			break ;
// 		printf("line\t-\t%.2i\t-\t%s", count++, line);
// 		free(line);
// 	}
// 	printf("\n");
// }