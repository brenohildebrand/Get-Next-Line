/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:11:20 by bhildebr          #+#    #+#             */
/*   Updated: 2023/08/15 17:35:01 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Get next line.
 * 
 * Receives a file descriptor and returns a pointer to a dynamic allocated
 * buffer storing the characters of the next line. It's meant to be called
 * successively. If there are no more lines returns null.
 * 
 * @param fd A file descriptor
 * @return A pointer to the next line or NULL if no such line exists. 
*/
char	*get_next_line(int fd)
{
	static char	*line = 0;

	free(line);
	line = read_line(fd);
	return (line);
}
