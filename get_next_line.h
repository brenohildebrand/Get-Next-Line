/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_netx_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhildebr <bhildebr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:29:45 by bhildebr          #+#    #+#             */
/*   Updated: 2023/08/28 14:29:45 by bhildebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/**
 * Defines BUFFER_SIZE if not defined yet.
*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/**
 * Define boolean values.
*/
# define TRUE 1
# define FALSE 0

/**
 * Include the headers matching the available functions for the project.
*/
# include <stdlib.h>
# include <unistd.h>

/**
 * Declare the prototypes.
*/
char	*get_next_line(int fd);
void	ft_free(void *p);

/**
 * Define a t_list type that will be used to store data from the fd. It's a
 * linked list.
*/
typedef struct s_list {
	char	*content;
	s_list	*next;
}	t_list;

#endif