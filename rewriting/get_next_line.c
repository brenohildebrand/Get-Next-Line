/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:13:15 by bhildebr          #+#    #+#             */
/*   Updated: 2023/09/06 17:31:45 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int	read_from_file_to_list(int fd, t_gnl *d)
{
	t_list	*new_node;
	t_list	*_list;
	int		_;
	int		a_newline_was_found;
	int		nread;

	_list = d->list;
	while (1)
	{
		new_node = malloc(sizeof(t_list));
		if (new_node == NULL)
			return (-1);
		new_node->content = malloc(BUFFER_SIZE * sizeof(char));
		if (new_node->content == NULL)
			return (-1);
		_ = 0;
		while (_ < BUFFER_SIZE)
			new_node->content[_++] = '\0';
		new_node->next = NULL;
	
		nread = read(fd, new_node->content, BUFFER_SIZE);
		if (nread == -1)
		{
			free(new_node->content);
			free(new_node);
			return (-1);
		}

		if (nread == 0)
		{
			if (d->list != NULL)
				(d->nlines)++;
			free(new_node->content);
			free(new_node);
			return (0);
		}
		
		if (d->list == NULL)
		{
			d->list = new_node;
			_list = new_node;	
		}
		else
		{
			while (_list->next != NULL)
				_list = _list->next;
			_list->next = new_node;
		}

		_ = 0;
		a_newline_was_found = 0;
		while (_ < BUFFER_SIZE)
		{
			if (new_node->content[_] == '\n')
			{
				(d->nlines)++;
				a_newline_was_found = 1;
			}
			_++;
		}
		if (a_newline_was_found)
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
	get_line_from_list(&data);
	if (data.line)
		return (data.line);
	read_from_file_to_list(fd, &data);
	get_line_from_list(&data);
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