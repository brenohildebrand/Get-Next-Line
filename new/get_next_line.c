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

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <stdio.h>

typedef struct	s_buffer {
	char			content[BUFFER_SIZE];
	unsigned int	size;
}	t_buffer;

typedef struct	s_line {
	char			*content;
	unsigned int	size;
	unsigned int	previous_size;
}	t_line;

char	*get_next_line(int fd)
{
	static t_buffer	buffer = {.content = NULL, .size = 0};
	static t_line	line = {.content = NULL, .size = 0, .previous_size = 0};

	free(line.content);
	line.content = NULL;

	start:

	// look for a newline in buffer
	int found_newline;
	int	found_newline_at;

	found_newline = 0;
	while (i < buffer.end)
	{
		if (buffer.content[i] == '\n')
		{
			found_newline = 1;
			found_newline_at = i;
			break;
		}
		i++;
	}

	// calculate total size for the line realloc
	int new_line_size;

	new_line_size = 0;
	new_line_size += line.size;
	if (found_newline)
		new_line_size += found_newline_at + 1;
	else
		new_line_size += buffer.size;
	line.previous_size = line.size;
	line.size = new_line_size;

	// realloc line
	char	*new_line_content;
	new_line_content = malloc(new_line_size);
	if (new_line_content = NULL)
		return (NULL);
	free(line.content);
	line.content = new_line_content;

	// copy from buffer to line
	int	i;

	i = 0;
	if (found_newline)
	{
		while (i <= found_newline_at)
		{
			line.content[line.previous_size + i] = buffer.content[i];
			i++;
		}
	}
	else
	{
		while (i < buffer.size)
		{
			line.content[line.previous_size + i] = buffer.content[i];
			i++;
		}
	}


	// shift buffer (copy from buffer to buffer)
	int	i;

	i = 0;
	if (found_newline)
	{
		while (i <= found_newline_at)
		{
			buffer.content[i] = buffer.content[found_newline_at + i];
			i++;
		}
		buffer.size = bufer.size - found_newline_at + 1;
	}
	else
	{
		buffer.size = 0;
	}

	// read from fd
	int	nread;

	nread = read(fd, &buffer.content, BUFFER_SIZE);

	if (nread == -1)
	{
		free(line.content);
		return (NULL);
	}

	if (nread == 0)
	{
		if (line)
			return (line.content);
		return (NULL);
	}

	if (nread > 0)
	{
		buffer.end = nread;
		goto start;
	}
}