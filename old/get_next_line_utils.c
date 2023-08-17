/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:38:57 by bhildebr          #+#    #+#             */
/*   Updated: 2023/08/15 19:45:36 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static void	handle_read_on_error(char **line, int *should_return)
{
	free(*line);
	*line = NULL;
	*should_return = 1;
}

static void	handle_read_on_end(char **line, int *i, int *should_return)
{
	if (*i == 0)
	{
		free(*line);
		*line = NULL;
	}
	else
	{
		(*line)[*i] = 0;
	}
	*should_return = 1;
}

static void	handle_read_on_success(char **line, int *i, int *should_return)
{
	int		j;
	char	*new_line;

	if ((*line)[*i] == '\n')
		*should_return = 1;
	else
	{
		new_line = malloc((*i + 2) * sizeof(char));
		if (new_line == NULL)
		{
			free(*line);
			*should_return = 1;
			return ;
		}
		j = 0;
		while (j < (*i + 1))
		{
			new_line[j] = (*line)[j];
			j++;
		}
		free(*line);
		*line = new_line;
	}
	(*i)++;
}

/**
 * Read file descriptor till a newline character.
 * 
 * @param fd File descriptor
 * @return A pointer to the allocated line.
*/
char	*read_line(int fd)
{
	char	*line;
	int		err;
	int		i;
	int		should_return;

	line = malloc(BUFFER_SIZE);
	if (line == NULL)
		return (NULL);
	i = 0;
	should_return = 0;
	while (should_return == 0)
	{
		err = read(fd, &line[i], BUFFER_SIZE);
		if (err == -1)
			handle_read_on_error(&line, &should_return);
		else if (err == 0)
			handle_read_on_end(&line, &i, &should_return);
		else if (err > 0)
			handle_read_on_success(&line, &i, &should_return);
	}
	return (line);
}
