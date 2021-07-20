#include "minishell.h"

char	*get_filename(void *data)
{
	return ((char *)data);
}

void	close_fds(int **fds)
{
	while (fds && *fds)
	{
		**fds > 2 && close(**fds);
		*(*fds + 1) > 2 && close(*(*fds + 1));
		fds++;
	}
}

void	pr(void*data)
{
	printf("'%s' ", (char *)data);
}
