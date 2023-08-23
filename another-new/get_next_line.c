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

typedef struct s_data {
	t_buffer	buffer;
	t_line		line;
}	t_data;

char	*get_next_line(int fd)
{
	static t_data data = {
		.buffer = {.size = 0},
		.line = {.content = 0, .size = 0, .previous_size = 0}
	};

	if (fd < 0)
		return (NULL);

	free(data.line.content);
	data.line.content = NULL;
	data.line.size = 0;

	while(1)
	{
		// look for a newline in buffer
		printf("LOOKING FOR A NEWLINE IN BUFFER:\n");
		printf("BUFFER SIZE IS = %d\n", data.buffer.size);
		int				i;
		int 			found_newline;
		int				found_newline_at;

		i = 0;
		found_newline = 0;
		while (i < data.buffer.size)
		{
			printf("current character = %x\n", data.buffer.content[i]);
			if (data.buffer.content[i] == '\n')
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
		new_line_size += data.line.size;
		if (found_newline)
			new_line_size += found_newline_at + 1;
		else
			new_line_size += data.buffer.size;
		data.line.previous_size = data.line.size;
		data.line.size = new_line_size;
		printf("new_line_size = %d\n", new_line_size);

		// realloc line
		printf("REALLOCING LINE:\n");
		char	*new_line_content;
		if (new_line_size > 0)
		{
			new_line_content = malloc(new_line_size);
			if (new_line_content == NULL)
			{
				free(data.line.content);
				return (NULL);
			}
		}
		else 
			new_line_content = NULL;
		i = 0;
		while (i < data.line.previous_size)
		{
			new_line_content[i] = data.line.content[i];
			i++;
		}
		free(data.line.content);
		data.line.content = new_line_content;
		printf("new_line_content = %p\n", new_line_content);

		// copy from buffer to line
		printf("COPYING FROM BUFFER TO LINE:\n");
		i = 0;
		if (found_newline)
		{
			while (i <= found_newline_at)
			{
				data.line.content[data.line.previous_size + i] = data.buffer.content[i];
				i++;
			}
		}
		else
		{
			while (i < data.buffer.size)
			{
				data.line.content[data.line.previous_size + i] = data.buffer.content[i];
				i++;
			}
		}
		printf("LINE = ");
		for (int z = 0; z < data.line.size; z++)
			printf("%c", data.line.content[z]);
		printf("\n");

		// shift buffer (copy from buffer to buffer)
		printf("SHIFTING BUFFER:\n");
		i = 0;
		if (found_newline)
		{
			while (i + found_newline_at + 1 < data.buffer.size)
			{
				data.buffer.content[i] = data.buffer.content[found_newline_at + i + 1];
				i++;
			}
			data.buffer.size = data.buffer.size - (found_newline_at + 1);
		}
		else
		{
			data.buffer.size = 0;
		}

		printf("BUFFER = ");
		for (int z = 0; z < data.buffer.size; z++)
			printf("%c", data.buffer.content[z]);
		printf("\n");

		if (found_newline)
		{
			printf("RETURNING LINE SINCE A LINE WAS FOUND\n");
			return (data.line.content);
		}

		// read from fd
		printf("READING FROM FD:\n");
		int	nread;

		nread = read(fd, &data.buffer.content, BUFFER_SIZE);

		if (nread == -1)
		{
			printf("AN ERROR OCURRED!\n");
			free(data.line.content);
			return (NULL);
		}

		if (nread == 0)
		{
			printf("END OF FILE\n");
			if (data.line.content)
				return (data.line.content);
			return (NULL);
		}

		if (nread > 0)
		{
			printf("BUFFER = ");
			for (int k = 0; k < nread; k++)
				printf("%c", data.buffer.content[k]);
			printf("\n");
			data.buffer.size = nread;
		}
	}

	return (NULL);
}