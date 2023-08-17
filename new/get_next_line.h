#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 8

char	*get_next_line(int fd);