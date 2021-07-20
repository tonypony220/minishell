#include "minishell.h"

int	execute_builtin(struct s_process *ps)
{
	(ps->status & HEREDOC) && msh_heredoc(ps);
	VERBOSE && printf(CYAN">>executing command builit %s %s\n"RESET,
			ps->args[0], ps->args[1]);
	ft_strcmp(ps->path, "echo") || msh_echo(ps);
	ft_strcmp(ps->path, "export") || msh_export(ps);
	ft_strcmp(ps->path, "pwd") || msh_pwd(ps);
	ft_strcmp(ps->path, "env") || msh_env(ps);
	ft_strcmp(ps->path, "exit") || msh_exit(ps);
	ft_strcmp(ps->path, "cd") || msh_cd(ps);
	ft_strcmp(ps->path, "unset") || msh_unset(ps);
	if (!(ps->status & DIRECT))
		exit(ps->exit_code);
	return (0);
}

/* It's not strighforward way to detect leaks in child process,
 * so to save time those are won't be hadleled.
 * Closing fds is reuquired, cause pipes waits for closing 
 * all it's end or EOF */
int	create_new_process(struct s_process *ps)
{
	int		pid;

	VERBOSE && printf(CYAN">>forking process %s %s %s\n"RESET,
			GREEN, ps->args[0], RESET);
	((pid = fork()) == -1) && err("fork failed");
	if (pid == CHILD_PID)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		ps->fd[OUT] > 2 && ((dup2(ps->fd[OUT], OUT) >= 0) || err("dup2"));
		ps->fd[IN] > 2 && ((dup2(ps->fd[IN], IN) >= 0) || err("dup2"));
		close_fds(ps->fds);
		ps->file[IN] && close(ps->fd[IN]);
		ps->file[OUT] && close(ps->fd[OUT]);
		(ps->status & BUILTIN) && execute_builtin(ps);
		execve(ps->path, ps->args, ft_lst_to_strs(ps->env, dict_to_str));
		display_err(ps);
		if (errno == 2)
			exit(CMD_NOT_FOUND_CODE);
		exit(EXIT_FAILURE);
	}
	return (1);
}

void	end_process(void *proc)
{
	struct s_process	*ps;

	ps = (struct s_process *)proc;
	(*ps).file[OUT] && close((*ps).fd[OUT]);
	(*ps).file[IN] && close((*ps).fd[IN]);
	(ps->status & SKIP) && (ps->shell->last_exit_code = 1);
	(ps->status & SKIP) || wait_process(ps);
}

int	wait_process(struct s_process *ps)
{
	int	status;
	int	exit_code;

	status = 0;
	ps->exit_code || (ps->status & DIRECT) || wait(&status);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	if (WTERMSIG(status) == SIGQUIT)
		printf("Quit\n");
	if (WIFSIGNALED(status))
	{
		write(1, "\r", 1);
		exit_code = WTERMSIG(status) + 128;
	}
	exit_code && (ps->exit_code = exit_code);
	ps->exit_code && (exit_code = ps->exit_code);
	ps->shell->last_exit_code = exit_code;
	VERBOSE && printf(CYAN"\t\tExit code: %d (%s)"RESET"\n",
		ps->shell->last_exit_code, *ps->args);
	return (0);
}

int	handle_processes(t_list *cmd)
{
	int	redirs;
	int	**fds;
	int	flag;

	fds = 0;
	redirs = 0;
	ft_lstiter_arg(cmd, count_redirections, &redirs);
	VERBOSE && printf("start hadnling cmds... %d pipes <<\n", redirs);
	redirs && (fds = (int **)multalloc(redirs, 0, sizeof(int)));
	flag = redirs;
	ft_lstiter_arg(cmd, set_fds_to_ps, fds);
	ft_lstiter_arg(cmd, set_flag_to_ps, &flag);
	ft_lstiter(cmd, start_process);
	close_fds(fds);
	freemultalloc((void **)fds);
	ft_lstiter(cmd, end_process);
	return (1);
}
