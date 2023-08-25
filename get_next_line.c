#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#ifndef ERROR_PROMPT
# define ERROR_PROMPT ">> "
#endif

void	assert(const char expression, const char *message)
{
	if (expression == 1)
		return ;
	printf("\033[31m[ERROR]\033[0m");
	// printf(" %s:%d ", __FILE__, __LINE__);
	// printf("%s", ERROR_PROMPT);
	printf("%s", message);
	exit(1);
}

int	ft_strlen(char *str)
{
	int	len;
	
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_appendstr(char **buffer, char *chunk)
{
	int		i;
	int		j;
	char	*new_buffer;

	new_buffer = malloc(ft_strlen(*buffer) + ft_strlen(chunk) + 1);
	i = 0;
	while ((*buffer)[i])
	{
		new_buffer[i] = (*buffer)[i];
		i++;
	}
	j = 0;
	while (chunk[j])
	{
		new_buffer[i + j] = chunk[j];
		j++;
	}
	new_buffer[i + j] = '\0';
	free(*buffer);
	*buffer = new_buffer;
}

int	populate_buffer(int fd, char **buffer)
{
	char	chunk[BUFFER_SIZE];
	int		nread;

	nread = read(fd, chunk, BUFFER_SIZE);
	if (nread == -1)
		return (-1);
	chunk[nread] = '\0';
	while (nread > 0 && /* chunk does not contain a newline character */)
	{
		if(ft_appendstr(buffer, chunk) == -1)
			return (-1);
		nread = read(fd, chunk, BUFFER_SIZE);
		if (nread == -1)
			return (-1);
		chunk[nread] = '\0';
	}
	return (0);
}

void	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (buffer == NULL)
	{
		buffer = malloc(1 * sizeof(char));
		if (buffer == NULL)
			return (NULL);
		buffer[0] = '\0';
	}
	line = NULL;
	if(populate_buffer(fd, &buffer) == -1)
	{
		free(line);
		free(buffer);
		return (NULL);
	}
	line = get_line_from_buffer(buffer);
	clean_buffer(&buffer);
	return (line);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else
			printf("%s", line);
	}
	printf("\n");
}