#include <stdlib.h>
#include "get_next_line.h"

# define TEXT "hello world"

int main(void)
{
	char *a = NULL;
	char *b = NULL;
	char *c = NULL;
	char *d = NULL;
	char *e = NULL;
	char *s = ft_substr(TEXT, 0, ft_strlen(TEXT));

	ft_assign_s(&a, s);
	ft_assign_s(&b, a);
	ft_assign_s(&c, b);
	ft_assign_s(&d, c);
	ft_assign_s(&e, d);
	
	free(e);
	return (0);
}