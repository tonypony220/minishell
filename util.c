#include "minishell.h"

void	*get_filename(void *data)
{
	return (data);
}

struct s_file	*new_file(char *filename, int std)
{
	struct s_file	*new;

	new = malloc(sizeof(struct s_file));
	if ((new))
	{
		new->filename = filename;
		new->std = std;
	}
	return (new);
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
	struct s_file	*f;

	f = data;
	printf("'%s'[%d] ", f->filename, f->std);
}
