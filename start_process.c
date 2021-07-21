#include "minishell.h"

int	assign_status_to_ps(struct s_process *ps, int stat)
{
	return ((ps->status |= stat));
}

int	files_redirects(struct s_process *ps)
{
	int				flag;
	struct s_file	*file;

	flag = 0;
	file = (struct s_file *)(ft_lstgen(ps->files, get_filename));
	while (file)
	{
		(*ps).fd[file->std] && close((*ps).fd[file->std]);
		if (file->std == OUT)
		{
			flag = O_WRONLY | O_CREAT;
			((*ps).status & A_FILE) && (flag |= O_APPEND);
			!((*ps).status & A_FILE) && (flag |= O_TRUNC);
			((*ps).fd[OUT] = open(file->filename, flag, 0644));
		}
		else
			((*ps).fd[IN] = open(file->filename, O_RDONLY, 0644));
		ps->file[file->std] = file->filename;
		if ((*ps).fd[file->std] == -1
			&& assign_status_to_ps(ps, SKIP)
			&& display_err(ps))
			return (0);
		file = (struct s_file *)(ft_lstgen(ps->files, get_filename));
	}
	return (1);
}

/* 
 * 	 cases [-1][0] [0][1]
 * 	   [0] [ 0][1] [1][2]  1 pipe, 2 file
 */
void	start_process(void *proc)
{
	struct s_process	*ps;
	int					pipe_number;

	ps = (struct s_process *)proc;
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
	print_process(ps);
	if (!files_redirects(ps) || (!ps->args[0])
		|| (ps->status & SKIP) || (ps->status & ONLY_FILE))
		return ;
	dispatching_process(ps);
	if (((*ps).exit_code) == 0)
	{
		!((*ps).status & DIRECT) && create_new_process(ps);
		((*ps).status & DIRECT) && execute_builtin(ps);
	}
}
