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

/**
 * @brief Try to find a line in the list and returns it. If the line does not
 * exist returns NULL. Note that this function will change the list state by
 * removing the line from it.
*/
char	*get_line_from_list(t_list *list)
{
	char	*line;


	return (line);
}

/**
 * @brief Returns the next line given a file descriptor.
 * @param fd file descriptor (a non-negative number indicating a file).
 * @internal Describe the function internals here.
*/
char	*get_next_line(int fd)
{
	static char	*line = NULL;
	t_list		*list = NULL;

	// free the line if it exists and set it to NULL
	// read buffer_size
	// analyze to see if it should stop reading and save the index where the line ends
	// create a copy of the line while freeing the list
	// returns the line

	
}