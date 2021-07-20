#include "minishell.h"

void set_fds_to_ps(void *proc, void *fds)
{
	struct process *ps;

	ps = (struct process*)proc;
	ps->fds = fds;
}

void set_flag_to_ps(void *proc, void *flag)
{
	struct process *ps;

	ps = (struct process*)proc;
	ps->flag = flag;
}

char					*get_filename(void* data)
{
	return ((char*)data);
}

void		close_fds(int **fds)
{
	while (fds && *fds)
	{
		**fds > 2 && close(**fds);
		*(*fds + 1) > 2 && close(*(*fds + 1));
		fds++;
	}
}

void pr(void*data)
{
	printf("'%s' ",(char*)data);
}

void	print_process(void *proc)
{
	struct process *ps;
	char *filename;
	int i;

	if (!VERBOSE) 
		return ;
	i = 0;
	ps = (struct process*)proc;
	printf(CYAN"PROCESS {%s}", ps->path);
	printf(CYAN" args[");
	while (ps->args[i])	
	{
		printf("(%s) ", ps->args[i]);
		i++;
	}
	printf("] PIPE(%d  %d) FD (%d %d) ",
		   ps->pipe[0],
		   ps->pipe[1],
		   ps->fd[0],
		   ps->fd[1]
		   );
	printf("\nFILES IN: ");
	ft_lstiter(ps->files_in, pr);
	printf("\nFILES OUT: ");
	ft_lstiter(ps->files_out, pr);
	printf("\nBUILTIN:(%d) DIRECT:(%d) REDIRECT=%d, HEREDOC=%d)\n"RESET,
		   ps->status & BUILTIN && 1,
		   ps->status & DIRECT && 1,
		   ps->status & A_FILE && 1,
		   ps->status & HEREDOC && 1
		   );
}

