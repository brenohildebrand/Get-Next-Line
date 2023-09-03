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
 * @brief Returns 1 if there's a newline character on the list or 0 otherwise.
*/
int	traverse_to_find_line(t_list *list, int was_file_completely_read)
{
	long long unsigned int i;

	i = 0;
	while (list && list->content[i] != '\n')
	{
		i++;
		if (i == BUFFER_SIZE)
		{
			i = 0;
			list = list->next;
		}
	}
	if (list && list->content[i] == '\n')
		return (1);
	else if (list == NULL && was_file_completely_read)
		return (1);
	else
		return (0);
}

/**
 * @brief
*/
char	*traverse_to_get_line(t_list *list, int was_file_completely_read)
{
	long long unsigned int	i;
	char					*line;
	char					*line_start;

	i = 0;
	line_start = malloc(BUFFER_SIZE * sizeof(char));
	line = line_start;
	if (line == NULL)
		return (NULL);
	while (list && list->content[i])
	{
		*line = list->content[i] != '\n';
		line++;
		i++;
		if (i == BUFFER_SIZE)
		{
			i = 0;
			list = list->next;
			// realloc line
		}
	}
	if (list && list->content[i] == '\n')
	{
		*line = list->content[i];
		line++;
	}
	*line = '\0';
	return (line_start);
}

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
			return (1);
		i++;
	}
	return (0);
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

// #include <stdio.h>

// int main(void)
// {
// 	t_list	*l;

// 	l = malloc(sizeof(t_list));
// 	l->content = "hello world hello again and again";
// 	l->next = NULL;

// 	printf("%d\n", traverse_to_find_line(l, 1));

// 	return (0);
// }