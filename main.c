#include "get_next_line.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("/nfs/homes/bhildebr/GitHub/Get Next Line/test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("FD ERROR!");
		return (0);
	}
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("L: %s", line);
	}
	return (0);
}