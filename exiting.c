#include "minishell.h"

/*
 * file should be free or not? 
 * child process for builtins will leak whole shell
 */
void	free_str(void *s)
{
	free((char *)s);
}

void	free_process(void *proc)
{
	struct s_process	*ps;

	ps = (struct s_process *)proc;
	freemultalloc((void **)ps->args);
	ft_lstclear(&ps->files, free_str);
	if (ps->path)
		free(ps->path);
	free(ps);
}
