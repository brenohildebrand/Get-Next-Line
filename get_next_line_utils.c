/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:26:25 by bhildebr          #+#    #+#             */
/*   Updated: 2023/08/28 14:26:25 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Look for the char c in the buffer s returning 1 if it's found or
 * 0 if it's not.
 * @note The size of the buffer should be exactly BUFFER_SIZE.
*/
int	ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (s[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

/**
 * 
*/
char	*get_line(t_list *list, int flag, int length)
{
	int		idx;
	int		list_idx;
	char	*line;

	line = malloc((length + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	idx = 0;
	list_idx = 0;
	while (list != NULL)
	{
		while (idx < BUFFER_SIZE)
		{
			line[(BUFFER_SIZE * list_idx) + idx] = list->content[i];
			idx++;
		}
		idx = 0;
		list_idx += 1;
		free(list->content);
		free(list);
		list = list->next;
	}
	line[(BUFFER_SIZE * list_idx) + idx] = '\0';
	return (line);
}

/**
 * 
*/
int get_line_length(t_list *list, int flag)
{
	int	length;

	length = 0;
	while (list != NULL)
	{
		length += BUFFER_SIZE
		if (ft_strchr(list->content, '\n') == TRUE)
			break ;
		list = list->next;
	}
	length += 1;
	return (length);
}

/**
 * 
*/
int	ft_lstchr(t_list *list, char c)
{
	while (list != NULL)
	{
		if (ft_strchr(list->content, c) == TRUE)
			return (TRUE);
		list = list->next;
	}
	return (FALSE);
}

/**
 * @brief Read BUFFER_SIZE bytes from fd to current_node.
 * @internal Read to the already allocated current_node BUFFER_SIZE bytes from
 * fd.
*/
char	*read_from_fd_to_current_node(int fd, t_list *current_node, int *pflag)
{
	int	read_return;

	read_return = read(fd, current_node->content, BUFFER_SIZE);
	if (read_return == -1)
	{
		free(current_node);
		return (NULL);
	}
	else if (read_return == 0)
	{
		*pflag = 1;
		free(current_node);
		return (NULL);
	}
	else
	{
		return (current_node);
	}
}
