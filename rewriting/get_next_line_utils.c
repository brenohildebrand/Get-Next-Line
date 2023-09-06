/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:13:17 by bhildebr          #+#    #+#             */
/*   Updated: 2023/09/06 17:30:33 by bhildebr         ###   ########.fr       */
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

void	copy_from_list_to_line(t_gnl *d)
{
	t_list	*_list;
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
			{
				_list = d->list;
				d->list = d->list->next;
				free(_list->content);
				free(_list);
				d->index = 0;
			}
			line_index++;
			break ;
		}
		else
		{
			_list = d->list;
			d->list = d->list->next;
			free(_list->content);
			free(_list);
			d->index = 0;
		}
	}
	d->line[line_index] = '\0';
}
