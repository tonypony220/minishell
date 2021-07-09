#include "../minishell.h"

void	print_cmd(t_shell *shell)
{
	while (shell->token)
	{
		ft_putendl(shell->token->token, 1);
		//printf("%s\nPIPE IN [%d] -- PIPE OUT [%d] -- PIPE# [%d]\n", shell->token->token, shell->token->pipe[0], shell->token->pipe[1], shell->token->_pipe);
		shell->token = shell->token->next;
	}
}

int	mini_exec(char **line, t_shell *shell)
{
	pid_t pid, wpid;
	int status;

	if (line == NULL)
		return (1);
	pid = fork();
	if (pid == 0) // Child process
	{
		print_command(shell);
/* 		if (execvp(line[0], line) == -1) // change to execve
			perror("MINISHELL"); */
		exit(0);
	}
	else if (pid < 0) // error
		ft_putendl("Error forking\n", 0);
	else // Parent process
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
    		wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

/* int		mini_cmd(t_shell *shell)
{
	if (shell->pars.has_pipe)
		do_pipe_stuff(shell); // PIPE FUNC HERE ??
	while (shell->pars.semi_colon > 0)
	{
		do_cmd_stuff(shell); // default stuff
		shell->pars.semi_colon--;
	}
} */
