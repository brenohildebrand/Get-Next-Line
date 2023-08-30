/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:54:50 by bhildebr          #+#    #+#             */
/*   Updated: 2023/08/28 10:54:50 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_gnl {
	char	*all;
	char	*line;
	int		reached_end_of_file;
}	t_gnl;

void	ft_free(char **p)
{
	free(*p);
	*p = NULL;
}

void	ft_assign_s(char **ps1, char *s2)
{
	free(*ps1);
	*ps1 = s2;
}

int	get_line(t_gnl *pdata)
{
	int	pos;

	if (ft_strlen(pdata->all) > 0)
	{
		pos = ft_strchr_i(pdata->all, '\n');
		if (pdata->reached_end_of_file && pos == -1)
			pos = ft_strlen(pdata->all) - 1;
		if (pos != -1)
		{
			ft_assign_s(&(pdata->line), ft_substr(pdata->all, 0, pos));
			ft_assign_s(\
				&(pdata->all), \
				ft_substr(pdata->all, pos + 1, ft_strlen(pdata->all) - 1) \
			);
			return (1);
		}
	}
	return (0);
}

int	read_file(int fd, t_gnl *pdata)
{
	int		n;
	char	b[BUFFER_SIZE];
	char	*aux;

	n = read(fd, b, BUFFER_SIZE);
	if (n == -1 || (n == 0 && pdata->reached_end_of_file))
	{
		ft_free(&(pdata->all));
		ft_free(&(pdata->line));
		return (-1);
	}
	else if (n == 0)
		pdata->reached_end_of_file = TRUE;
	else if (n > 0)
	{
		aux = NULL;
		ft_assign_s(&aux, ft_substr(b, 0, n - 1));
		ft_assign_s(&(pdata->all), ft_strjoin(pdata->all, aux));
		free(aux);
		if (pdata->all == NULL)
			return (-1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_gnl	data = {
		.all = NULL,
		.line = NULL,
		.reached_end_of_file = FALSE,
	};

	if (data.all == NULL)
	{
		ft_assign_s(&(data.all), ft_newstr());
		if (data.all == NULL)
			return (NULL);
	}
	if (data.line != NULL)
	{
		free(data.line);
		data.line = NULL;
	}
	if (get_line(&data) == 1)
		return (data.line);
	if (read_file(fd, &data) == -1)
		return (NULL);
	return (get_next_line(fd));
}
