#include "get_next_line.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	int		line_number;
	char	*line;

	line_number = 1;
	fd = open("/mnt/c/users/breno/GitHub/Get-Next-Line/test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("FD ERROR!\n");
		return (0);
	}
	loop
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%2i: %s", line_number++, line);
	}
	printf("\n");
	return (0);
}