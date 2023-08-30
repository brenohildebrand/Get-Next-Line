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

#include <stdlib.h>

char	*ft_newstr(void)
{
	char	*s;

	s = malloc(sizeof(char));
	if (s == NULL)
		return (NULL);
	s[0] = '\0';
	return (s);
}

long long int	ft_strlen(char *s)
{
	long long int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	long long int	i;
	long long int	j;
	char			*s3;

	if (s1 == NULL && s2 == NULL)
		return (ft_newstr());
	if (s1 == NULL)
		return (s2);
	else if (s2 == NULL)
		return (s1);
	s3 = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	j = -1;
	while (s2[++j])
		s3[i + j] = s2[j];
	s3[i + j] = '\0';
	return (s3);
}

char	*ft_substr(char *s, long long int start, long long int end)
{
	long long int	i;
	char			*new_s;

	if (end < start)
		return (ft_newstr());
	new_s = malloc(((end - start + 1) + 1) * sizeof(char));
	if (new_s == NULL)
		return (NULL);
	i = 0;
	while (start + i <= end)
	{
		new_s[i] = s[start + i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

long long int	ft_strchr_i(char *s, char c)
{
	long long int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}
