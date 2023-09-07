typedef struct s_list {
	char			*content;
	struct s_list	*next;
}	t_list;

void	free_list(t_list *l)
{
	t_list	*current_node;
	t_list	*next_node;

	current_node = l;
	next_node = l->next;
	while (current_node != NULL)
	{
		free(current_node->content);
		free(current_node);
		current_node = next_node;
		next_node = next_node->next;
	}
}

char	*get_next_line(int fd)
{
	static int		newline_index = 0;
	static int		newline_node_index = 0;
	static char		*line = NULL;
	static t_list	*list = NULL;

	// just check if there's something in the line and free it
	if (line != NULL)
		free(line);

	// allocate a node to read to
	t_list	*current_node;

	current_node = malloc(sizeof(t_list));
	if (current_node == NULL)
	{
		free_list(list);
		free(line);
		return (NULL);
	}
	current_node->content = malloc(BUFFER_SIZE * sizeof(char));
	if (current_node->content == NULL)
	{
		free(current_node);
		free_list(list);
		free(line);
		return (NULL);
	}

	current_node->next = NULL;

	// read to this node
	int	nread;

	nread = read(fd, current_node->content, BUFFER_SIZE);
	if (nread == -1)
	{
		free(current_node->content);
		free(current_node);
		free_list(list);
		free(line);
		return (NULL);
	}

	// move the newline mark to a newline

}