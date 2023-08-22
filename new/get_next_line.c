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
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_buffer {
	char			content[BUFFER_SIZE];
	int				size;
}	t_buffer;

typedef struct	s_line {
	char			*content;
	int				size;
	int				previous_size;
}	t_line;

char	*get_next_line(int fd)
{
	static t_buffer	buffer = {.size = 0};
	static t_line	line = {.content = 0, .size = 0, .previous_size = 0};

	free(line.content);
	line.content = NULL;
	line.size = 0;

	start:

	// look for a newline in buffer
	printf("LOOKING FOR A NEWLINE IN BUFFER:\n");
	printf("BUFFER SIZE IS = %d\n", buffer.size);
	int				i;
	int 			found_newline;
	int				found_newline_at;

	i = 0;
	found_newline = 0;
	while (i < buffer.size)
	{
		printf("current character = %x\n", buffer.content[i]);
		if (buffer.content[i] == '\n')
		{
			found_newline = 1;
			found_newline_at = i;
			break;
		}
		i++;
	}
	printf("found_newline = %d\n", found_newline);
	printf("found_newline_at = %d\n", found_newline_at);

	// calculate total size for the line realloc
	printf("CALCULATING SIZE FOR LINE REALLOC:\n");
	int new_line_size;

	new_line_size = 0;
	new_line_size += line.size;
	if (found_newline)
		new_line_size += found_newline_at + 1;
	else
		new_line_size += buffer.size;
	line.previous_size = line.size;
	line.size = new_line_size;
	printf("new_line_size = %d\n", new_line_size);

	// realloc line
	printf("REALLOCING LINE:\n");
	char	*new_line_content;
	if (new_line_size > 0)
	{
		new_line_content = malloc(new_line_size);
		if (new_line_content == NULL)
		{
			free(line.content);
			return (NULL);
		}
	}
	else 
		new_line_content = NULL;
	i = 0;
	while (i < line.previous_size)
	{
		new_line_content[i] = line.content[i];
		i++;
	}
	free(line.content);
	line.content = new_line_content;
	printf("new_line_content = %p\n", new_line_content);

	// copy from buffer to line
	printf("COPYING FROM BUFFER TO LINE:\n");
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
	printf("LINE = ");
	for (int z = 0; z < line.size; z++)
		printf("%c", line.content[z]);
	printf("\n");

	// shift buffer (copy from buffer to buffer)
	printf("SHIFTING BUFFER:\n");
	i = 0;
	if (found_newline)
	{
		while (i + found_newline_at + 1 < buffer.size)
		{
			buffer.content[i] = buffer.content[found_newline_at + i + 1];
			i++;
		}
		buffer.size = buffer.size - (found_newline_at + 1);
	}
	else
	{
		buffer.size = 0;
	}

	printf("BUFFER = ");
	for (int z = 0; z < buffer.size; z++)
		printf("%c", buffer.content[z]);
	printf("\n");

	if (found_newline)
	{
		printf("RETURNING LINE SINCE A LINE WAS FOUND\n");
		return (line.content);
	}

	// read from fd
	printf("READING FROM FD:\n");
	int	nread;

	nread = read(fd, &buffer.content, BUFFER_SIZE);

	if (nread == -1)
	{
		printf("AN ERROR OCURRED!\n");
		free(line.content);
		return (NULL);
	}

	if (nread == 0)
	{
		printf("END OF FILE\n");
		if (line.content)
			return (line.content);
		return (NULL);
	}

	if (nread > 0)
	{
		printf("BUFFER = ");
		for (int k = 0; k < nread; k++)
			printf("%c", buffer.content[k]);
		printf("\n");
		buffer.size = nread;
		goto start;
	}

	return (NULL);
}