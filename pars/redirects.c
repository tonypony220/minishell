#include "../minishell.h"

int		check_for_redir(struct process *ps)
{
	if (ps->redir_type == 4 || ps->redir_type == 1)
		redir_in(ps);
	else if (ps->redir_type == 2 || ps->redir_type == 3)
		redir_out(ps);
	
	return (1);
}

void	redir_in(struct process *ps)
{
	int fd;

	if (ps->redir_type == 4)
		fd = open(ps->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (ps->redir_type == 1)
		fd = open(ps->file, O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_out(struct process *ps)
{
	int fd;

	if (ps->redir_type == 3)
		fd = open(ps->file, O_RDONLY, 0644);
	else if (ps->redir_type == 2)
		fd = open(ps->file, O_RDONLY, 0644);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
