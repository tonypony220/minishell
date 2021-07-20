#include "minishell.h"

int	assign_status_to_ps(struct process *ps, int stat)
{
	return ((ps->status |= stat));
}

int	files_in_redirects(struct process *ps)
{
	int		flag;
	char	*filename;

	flag = 0;
	filename = (ft_lstgen(ps->files_in, get_filename));
	while (filename)
	{
		(*ps).fd[IN] && close((*ps).fd[IN]);
		((*ps).fd[IN] = open(filename, O_RDONLY, 0644));
		if ((*ps).fd[IN] == -1
			&& assign_status_to_ps(ps, SKIP)
			&& display_err(ps))
			return (0);
		ps->file[IN] = filename;
		filename = (ft_lstgen(ps->files_in, get_filename));
	}
	return (1);
}

int	files_out_redirects(struct process *ps)
{
	int		flag;
	char	*filename;

	flag = 0;
	filename = (ft_lstgen(ps->files_out, get_filename));
	while (filename)
	{
		(*ps).fd[OUT] && close((*ps).fd[OUT]);
		flag = O_WRONLY | O_CREAT;
		((*ps).status & A_FILE) && (flag |= O_APPEND);
		!((*ps).status & A_FILE) && (flag |= O_TRUNC);
		((*ps).fd[OUT] = open(filename, flag, 0644));
		if ((*ps).fd[OUT] == -1
			&& assign_status_to_ps(ps, SKIP)
			&& display_err(ps))
			return (0);
		ps->file[OUT] = filename;
		filename = (ft_lstgen(ps->files_out, get_filename));
	}
	return (1);
}

/* 
 * 	 cases [-1][0] [0][1]
 * 	   [0] [ 0][1] [1][2]  1 pipe, 2 file
 */
void	start_process(void *proc)
{
	struct process	*ps;
	int				pipe_number;

	ps = (struct process *)proc;
	if (ps->pipe[IN] != NO_PIPE)
	{
		pipe_number = (*ps).pipe[IN];
		ps->fd[IN] = ps->fds[pipe_number][IN];
	}
	if ((*ps).pipe[OUT] != NO_PIPE)
	{
		pipe_number = (*ps).pipe[OUT];
		(pipe(ps->fds[pipe_number]) == -1) && err("pipe creation failed");
		ps->fd[OUT] = ps->fds[pipe_number][OUT];
	}
	if (!files_in_redirects(ps) || !files_out_redirects(ps) || (!ps->args[0])
		|| (ps->status & SKIP) || (ps->status & ONLY_FILE))
		return ;
	dispatching_process(ps);
	print_process(ps);
	if (((*ps).exit_code) == 0)
	{
		!((*ps).status & DIRECT) && create_new_process(ps);
		((*ps).status & DIRECT) && execute_builtin(ps);
	}
}
