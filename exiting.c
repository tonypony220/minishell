#include "minishell.h"

//void	free_processes(struct process **ps)
//{
////	freemultalloc(ps[0]->fds);
////	ft_lstclear(ps[0]->env, del_dict);
////	ps--;
////	while (++ps)
////		free_process(ps, 1);
//}

/* 
 * file should be free or not? 
 * child process for builtins will leak whole shell
 */
//void	free_process(struct process *ps)
//{
//	freemultalloc(ps->args);
////	ft_lstclear();
//	if (ps->path)
//		free(ps->path);
//	free(ps);
//}

/* 
 * file should be free or not? 
 * child process for builtins will leak whole shell
 */
void free_str(void *s)
{
	free((char*)s);
}

void free_process(void *proc)
{
	struct process *ps;

	ps = (struct process *)proc;
	freemultalloc(ps->args);
	ft_lstclear(&ps->files_in, free_str);
	ft_lstclear(&ps->files_out, free_str);
	if (ps->path)
		free(ps->path);
	free(ps);
}
