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
	struct process	*ps;

	ps = (struct process *)proc;
	freemultalloc(ps->args);
	ft_lstclear(&ps->files_in, free_str);
	ft_lstclear(&ps->files_out, free_str);
	if (ps->path)
		free(ps->path);
	free(ps);
}
