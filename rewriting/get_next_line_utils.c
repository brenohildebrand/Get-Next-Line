/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:13:17 by bhildebr          #+#    #+#             */
/*   Updated: 2023/09/06 18:51:57 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*malloc_new_node()
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

static void	free_new_node(t_list *new_node)
{
	free(new_node->content);
	free(new_node);
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

static int	count_newlines(t_list *new_node)
{
	int	_;
	int nnewlines;
	
	_ = 0;
	nnewlines = 0;
	while (_ < BUFFER_SIZE)
	{
		if (new_node->content[_] == '\n')
			nnewlines++;
		_++;
	}
	return (nnewlines);
}

int	read_from_file_to_list(int fd, t_gnl *d)
{
	int		nread;
	t_list	*new_node;
	// t_list	*_list;
	// int		_;
	// int		a_newline_was_found;

	// _list = d->list;
	while (1)
	{
		// new_node = malloc(sizeof(t_list));
		// if (new_node == NULL)
		// 	return (-1);
		// new_node->content = malloc(BUFFER_SIZE * sizeof(char));
		// if (new_node->content == NULL)
		// 	return (-1);
		// _ = 0;
		// while (_ < BUFFER_SIZE)
		// 	new_node->content[_++] = '\0';
		// new_node->next = NULL;
		new_node = malloc_new_node();
		if (new_node == NULL)	
			return (-1);

		nread = read(fd, new_node->content, BUFFER_SIZE);
		if (nread == -1)
		{
			// free(new_node->content);
			// free(new_node);
			free_new_node(new_node);
			return (-1);
		}

		if (nread == 0)
		{
			if (d->list != NULL)
				(d->nlines)++;
			// free(new_node->content);
			// free(new_node);
			free_new_node(new_node);
			return (0);
		}
		
		// if (d->list == NULL)
		// {
		// 	d->list = new_node;
		// 	_list = new_node;	
		// }
		// else
		// {
		// 	while (_list->next != NULL)
		// 		_list = _list->next;
		// 	_list->next = new_node;
		// }

		// _ = 0;
		// a_newline_was_found = 0;
		// while (_ < BUFFER_SIZE)
		// {
		// 	if (new_node->content[_] == '\n')
		// 	{
		// 		(d->nlines)++;
		// 		a_newline_was_found = 1;
		// 	}
		// 	_++;
		// }
		// if (a_newline_was_found)
		// 	return (0);
		add_new_node_to_list(new_node, d);
		d->nlines += count_newlines(new_node);
		if (count_newlines(new_node))
			return (0);
	}
}