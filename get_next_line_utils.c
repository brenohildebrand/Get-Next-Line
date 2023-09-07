/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:13:17 by bhildebr          #+#    #+#             */
/*   Updated: 2023/09/07 14:40:15 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static t_list	*malloc_new_node(void)
{
	int		_;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = malloc(BUFFER_SIZE * sizeof(char));
	if (new_node->content == NULL)
		return (NULL);
	_ = 0;
	while (_ < BUFFER_SIZE)
		new_node->content[_++] = '\0';
	new_node->next = NULL;
	return (new_node);
}

static void	free_new_node_or_free_new_node_and_reset(\
t_gnl *d, \
t_list *new_node, \
int option)
{
	t_list	*_list;

	free(new_node->content);
	free(new_node);
	if (option == 1)
	{
		while (d->list != NULL)
		{
			_list = d->list;
			d->list = d->list->next;
			free(_list->content);
			free(_list);
		}
		d->nlines = 0;
		d->index = 0;
	}
}

static void	add_new_node_to_list(t_list *new_node, t_gnl *d)
{
	t_list	*_list;

	if (d->list == NULL)
		d->list = new_node;
	else
	{
		_list = d->list;
		while (_list->next != NULL)
			_list = _list->next;
		_list->next = new_node;
	}
}

static int	count_newlines(t_list *new_node, t_gnl *d)
{
	int	_;
	int	nnewlines;

	_ = 0;
	nnewlines = 0;
	while (_ < BUFFER_SIZE)
	{
		if (new_node->content[_] == '\n')
			nnewlines++;
		_++;
	}
	d->nlines += nnewlines;
	return (nnewlines);
}

int	read_from_file_to_list(int fd, t_gnl *d)
{
	int		nread;
	t_list	*new_node;

	while (1)
	{
		new_node = malloc_new_node();
		if (new_node == NULL)
			return (-1);
		nread = read(fd, new_node->content, BUFFER_SIZE);
		if (nread < 0)
		{
			free_new_node_or_free_new_node_and_reset(d, new_node, 1);
			return (-1);
		}
		if (nread == 0)
		{
			if (d->list != NULL)
				(d->nlines)++;
			free_new_node_or_free_new_node_and_reset(d, new_node, 0);
			return (0);
		}
		add_new_node_to_list(new_node, d);
		if (count_newlines(new_node, d))
			return (0);
	}
}
