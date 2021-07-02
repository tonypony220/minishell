#include "minishell.h"

void	free_processes(struct process **ps)
{
	freemultalloc(ps[0]->fds);
	ft_lstclear(ps[0]->env, del_dict);
	ps--;
	while (++ps)
		free_process(ps, 1);
}

/* 
 * file should be free or not? 
 * child process for builtins will leak whole shell
 */
void	free_process(struct process *ps, int child)
{
	freemultalloc(ps->args);
	//if (ps->file)
	//	free(ps->file);
	free(ps);
}
