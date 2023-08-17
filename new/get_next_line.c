/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:52:34 by bhildebr          #+#    #+#             */
/*   Updated: 2023/08/15 19:52:34 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

typedef struct s_buffer {
	void	*ptr;
	size_t	size;
}	t_buffer;

void	ft_memcpy(void *dest, void *src, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
	{
		((unsigned char *)dest)[index] = ((unsigned char *)src)[index];
		index++;
	}
}

void	ft_realloc(void **ptr, ssize_t n, ssize_t size)
{
	void	*new_ptr;

	new_ptr = malloc(size)
	if(new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr)
		ft_memcpy(new_ptr, ptr, n);
	free(ptr);
	ptr = new_ptr;
}

void	ft_memset(void *ptr, int c, size_t n)
{
	int	index;

	index = 0;
	while (index < n)
	{
		((unsigned char *)ptr)[index] = c;
		index++;
	}
}

ssize_t	ft_look_for_newline(void *buffer, ssize_t nread)
{
	ssize_t	index;

	index = 0;
	while (index < nread)
	{
		if (buffer[index] == '\n')
			return (index); 
		index++;
	}
	return (-1);
}

int	handle_buffer(void **buffer, void **line, ssize_t nread)
{
	int	index;
	int copy_length;
	int found_newline_at;

	found_newline_at = ft_look_for_newline(buffer, nread);
	// if found newline then (realloc line) and then (copy from 0 till found_newline_at to line) and (remove from 0 till found_newline_at from buffer) and (return 1 - meaning line is ready)
	if (found_newline_at == -1)
	{
		ft_realloc(line, nread - 1, )
		ft_memcpy(line, buffer, nread - 1);
		ft_memset(buffer, 0, nread - 1);
	}
	// else then (realloc line) and then (copy from 0 till nread - 1) and (remove from 0 till nread - 1)
	else
	{
		ft_memcpy(line, buffer, found_newline_at);
		ft_memset(buffer, 0, found_newline_at);
	}
}

char	*get_next_line(int fd)
{
	static void	*buffer[BUFFER_SIZE];
	char		*line;
	ssize_t		nread;

	line = NULL;
	is_line_ready = handle_buffer();
	while(!is_line_ready)
	{
		nread = read(fd, buffer, BUFFER_SIZE);
		if (nread == -1)
		{
			free(line)
			return (NULL)
		}
		else if (nread == 0)
			is_line_ready = 1;
		else if (nread > 0)
			is_line_ready = handle_buffer(&buffer, &line, nread);
	}
	return (line);
}