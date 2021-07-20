#include "minishell.h"

void	set_fds_to_ps(void *proc, void *fds)
{
	struct s_process	*ps;

	ps = (struct s_process *)proc;
	ps->fds = fds;
}

void	set_flag_to_ps(void *proc, void *flag)
{
	struct s_process	*ps;

	ps = (struct s_process *)proc;
	ps->flag = flag;
}

void	count_redirections(void *proc, void *redirs)
{
	struct s_process	*ps;

	ps = (struct s_process *)proc;
	if ((*ps).pipe[OUT] != NO_PIPE)
		*(int *)redirs += 1;
}

void	print_process(void *proc)
{
	struct s_process	*ps;
	int					i;

	if (!VERBOSE)
		return ;
	ps = (struct s_process *)proc;
	printf(CYAN"PROCESS {%s}", ps->path) && printf(CYAN" args[");
	i = -1;
	while (ps->args[++i])
		printf("(%s) ", ps->args[i]);
	printf("] PIPE(%d  %d) FD (%d %d) ", ps->pipe[0], ps->pipe[1],
		   ps->fd[0], ps->fd[1]);
	printf("\nFILES IN: ");
	ft_lstiter(ps->files_in, pr);
	printf("\nFILES OUT: ");
	ft_lstiter(ps->files_out, pr);
	printf("\nBUILTIN:(%d) DIRECT:(%d) REDIRECT=%d, HEREDOC=%d)\n"RESET,
		   ps->status & BUILTIN && 1,
		   ps->status & DIRECT && 1,
		   ps->status & A_FILE && 1,
		   ps->status & HEREDOC && 1);
}
