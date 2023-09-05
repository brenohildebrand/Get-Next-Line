/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 21:57:24 by bhildebr          #+#    #+#             */
/*   Updated: 2023/09/04 21:57:24 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// #define BUFFER_SIZE 1

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int		get_line_from_list(t_list **plist, char **line_address, int *number_of_lines)
{
	static int	index;
	int			length;

	int		line_index;
	t_list		*_list;

	// check for a line and it's size
	if (*number_of_lines > 0)
	{
		// get line length
		int	_index;
		
		_index = index;
		_list = *plist;
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

		// alloc line
		(*line_address) = malloc((length + 1) * sizeof(char));
		if ((*line_address) == NULL)
			return (-1);
		
		// copy from list to line
		line_index = 0;
		while (*plist != NULL)
		{
			while (index < BUFFER_SIZE)
			{
				(*line_address)[line_index] = (*plist)->content[index];
				if ((*plist)->content[index] == '\n')
				{
					break ;
				}
				index++;
				line_index++;
			}
			if (index < BUFFER_SIZE)
			{
				index++;
				if (index == BUFFER_SIZE || (*plist)->content[index] == '\0') // it will only have the next character being '\0' if it's the last line and you can free the list and mark it as NULL
				{
					_list = *plist;
					*plist = (*plist)->next;
					free(_list->content);
					free(_list);
					index = 0;
				}
				line_index++;
				break ;
			}
			else
			{
				_list = *plist;
				*plist = (*plist)->next;
				free(_list->content);
				free(_list);
				index = 0;
			}
		}
		(*line_address)[line_index] = '\0';

		// discount line
		(*number_of_lines)--;

		// return ok
		return (0);
	}
	else
	{
		return (0);
	}
}

// read from file to list till it finds a newline or the file ends
int		read_from_file_to_list(int fd, t_list **plist, int *number_of_lines)
{
	int		nread;
	t_list	*list;
	t_list	*new_node;
	
	while(1)
	{
		// alloc and init list
		new_node = malloc(sizeof(t_list));
		if (new_node == NULL)
			return (-1);
		new_node->content = malloc(BUFFER_SIZE * sizeof(char));
		if (new_node->content == NULL)
			return (-1);
		for (int i = 0; i < BUFFER_SIZE; i++)
			new_node->content[i] = '\0';
		new_node->next = NULL;

		// read to it
		nread = read(fd, new_node->content, BUFFER_SIZE);
		if (nread == -1)
			return (-1);
		
		// check if the file ends
		if (nread == 0)
		{
			if (*plist != NULL)
				(*number_of_lines)++;
			free(new_node->content);
			free(new_node);
			return (0);
		}

		// add it to list
		if (*plist == NULL)
		{
			*plist = new_node;
			list = new_node;
		}
		else
		{
			while (list->next != NULL)
				list = list->next;
			list->next = new_node;
		}

		// count the number of lines and check if a newline was found
		int	i;
		int	a_newline_was_found;

		i = 0;
		a_newline_was_found = 0;
		while (i < BUFFER_SIZE)
		{
			if (new_node->content[i] == '\n')
			{
				(*number_of_lines)++;
				a_newline_was_found = 1;
			}
			i++;
		}
		if (a_newline_was_found)
			return (0);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	static char		*line = NULL;
	static int		number_of_lines = 0;

	// check errors
	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, NULL, 0))
		return (NULL);
	// free line
	if (line != NULL)
	{
		free(line);
		line = NULL;
	}
	// get line if there's any
	if (get_line_from_list(&list, &line, &number_of_lines) == -1)
	{
		// treat error
	}
	if (line)
		return (line);
	// read to make sure there's a line
	if (read_from_file_to_list(fd, &list, &number_of_lines) == -1)
	{
		// treat error
	}
	// get line cause there's one... if there's not then it's the end
	if (get_line_from_list(&list, &line, &number_of_lines) == -1)
	{
		// treat error
	}
	if (line)
		return (line);
	// if didn't return at this point ... reset state and return NULL
	// reset state
	return (NULL);
}

// int	main(int argc, char *argv[])
// {
// 	int		fd;
// 	int		count;
// 	char	*line;

// 	// Test 00
// 	fd = open("test06.txt", O_RDWR);
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
// 	}
// 	printf("\n\n");
// 	close(fd);

// 	// Test 01
// 	fd = open("test01.txt", O_RDWR);
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
// 	}
// 	printf("\n\n");
// 	close(fd);

// 	// Test 02
// 	fd = open("test02.txt", O_RDWR);
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
// 	}
// 	printf("\n\n");
// 	close(fd);
// }