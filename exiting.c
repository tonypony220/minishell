#include "minishell.h"

/*
 * file should be free or not? 
 * child process for builtins will leak whole shell
 */
void	free_str(void *s)
{
	free((char *)s);
}

void	del_file(void *content)
{
	struct s_file	*d;

	d = (struct s_file *)content;
	free(d->filename);
	free(d);
}

void	free_process(void *proc)
{
	struct s_process	*ps;

	ps = (struct s_process *)proc;
	freemultalloc((void **)ps->args);
	ft_lstclear(&ps->files, del_file);
	if (ps->path)
		free(ps->path);
	free(ps);
}
