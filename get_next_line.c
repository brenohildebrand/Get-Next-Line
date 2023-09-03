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

// defining the details:
// the line will have a '\0' at the end
// the buffer size and the list nodes will not -> use BUFFER_SIZE

/**
 * @brief If a line exists on the list, returns it. Otherwise, returns NULL. 
 * @note This function will change the list state by removing the line 
 * from it.
*/
char	*get_line_from_list(t_list *list, int flag)
{
	if (traverse_to_find_line(list, flag))
		return (traverse_to_get_line(list, flag));
	else
		return (NULL);
}

/**
 * @brief Keeps reading BUFFER_SIZE bytes to list till a newline is found in
 * these BUFFER_SIZE bytes or till the end of the file. If the end of the file
 * is reached, set flag to 1.
*/
char	*read_from_fd_to_list(int fd, t_list *list, int *pflag)
{
	static t_list	*previous_node = NULL;
	t_list			*current_node;

	while (1)
	{
		current_node = malloc(BUFFER_SIZE * sizeof(t_list));
		if (current_node == NULL)
			return (NULL);
		current_node = read_from_fd_to_current_node(fd, current_node, pflag);
		if (current_node == NULL)
			return (NULL);
		previous_node->next = current_node;
		previous_node = current_node;		
		if (strchr(current_node->content, '\n') == TRUE)
			return (current_node->content);
	}
}

/**
 * @brief Returns the next line given a file descriptor.
 * @param fd file descriptor (a non-negative number indicating a file).
 * @internal Describe the function internals here.
*/
char	*get_next_line(int fd)
{
	static char		*line = NULL;
	static t_list	*list = NULL;

	while (1)
	{
		if (line != NULL)
			free(line);
		line = get_line_from_list(list);
		if (line != NULL)
			return (line);
		read_from_fd_to_list(list);
		if (list == NULL)
			return (NULL);
	}
}