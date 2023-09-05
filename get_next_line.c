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

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int		get_line_from_list(t_list *list, char **line_address, int *number_of_lines)
{
	static int	index;
	int			i;
	int			j;
	int			length;

	// check for a line and it's size
	if (number_of_lines > 0)
	{
		// get line length
		i = index;
		while (list != NULL)
		{
			while (i < BUFFER_SIZE)
			{
				if (list->content[i] == '\n')
				{
					length++;
					break ;
				}
				length++;
				i++;
			}
			if (i < BUFFER_SIZE)
			{
				break ;
			}
			i = 0;
			list = list->next;
		}

		// alloc line
		(*line_address) = malloc((length + 1) * sizeof(char));
		if ((*line_address) == NULL)
			return (-1);
		
		// copy from list to line
		int		counter;

		counter = 0;
		while (list != NULL)
		{
			while (index < BUFFER_SIZE)
			{
				(*line_address)[counter] = list->content[index];
				if (list->content[index] == '\n')
				{
					break ;
				}
				index++;
				counter++;
			}
			if (index < BUFFER_SIZE)
			{
				index++;
				if (index == BUFFER_SIZE)
					index = 0;
				counter++;
				break ;
			}
			index = 0;
			list = list->next;
		}
		(*line_address)[length] = '\0';

		// discount line
		number_of_lines--;

		// return ok
		return (0);
	}
	else
	{
		*line_address = NULL;
		return (0);
	}
}

// read from file to list till it finds a newline or the file ends
int		read_from_file_to_list(int fd, t_list *list, int *number_of_lines)
{
	int		nread;
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
			(*number_of_lines)++;
			free(new_node->content);
			free(new_node);
			return (0);
		}

		// add it to list
		while (list->next != NULL)
			list = list->next;
		list->next = new_node;

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
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	// free line
	if (line != NULL)
	{
		free(line);
		line = NULL;
	}
	// get line if there's any
	if (get_line_from_list(list, &line, &number_of_lines) == -1)
	{
		// treat error
	}
	if (line)
		return (line);
	// read to make sure there's a line
	if (read_from_file_to_list(fd, list, &number_of_lines) == -1)
	{
		// treat error
	}
	// get line cause there's one... if there's not then it's the end
	if (get_line_from_list(list, &line, &number_of_lines) == -1)
	{
		// treat error
	}
	if (line)
		return (line);
	// if didn't return at this point ... reset state and return NULL
	// reset state
	return (NULL);
}