#include "minishell.h"

/* commands:
 * cat >> file
 * cat | less file
 * ls | less >> file
 * echo 
 */

extern char** environ;

int last_exit_code;
int redirs_nbr;

int	err(char* err_str)

{
	perror(err_str);
	exit(1);
	return 1;  /* don't know how to force return int that compiler accept it*/
}

void		close_fds(int **fds)
{
	while (*fds)
	{
//		printf("closing fds\n");
		**fds > 2 && close(**fds);
		*(*fds + 1) > 2 && close(*(*fds + 1));
		fds++;
	}
//	printf("closed fds\n");
}

int			create_new_process(struct process *ps)
{
	/* param fd: waiting only fd to redirect, else 0 */
	int		pid;
	char	*path;

	if ((pid = fork()) == -1)
		err("fork failed"); // todo not exit
	else if (pid == CHILD_PID)
	{
		// todo BUILTINS
		path = find_path(ps->args[0]);
		printf("'%s' path args '%s' '%s'\n", path, ps->args[0], ps->args[1]);
		// todo how it exits if wrong path
		!path && err(ft_strjoin(ps->args[0], ": command not found"));

		ps->args[0] = path;
		printf("%s %d %d fds pipe %d %d\n", ps->args[0], ps->fd[IN], ps->fd[OUT], ps->pipe[IN], ps->pipe[OUT]);
		/* maybe enough for redirection todo check it */
		ps->fd[OUT] > 2 && ((dup2(ps->fd[OUT], OUT) >= 0) || err("dup2")); // && close(fd[OUT]);
		ps->fd[IN] > 2 && ((dup2(ps->fd[IN], IN) >= 0) || err("dup2"));// && close(fd[IN]);
		/* old version */
		//	ps->pipe[OUT] != -1 && ((dup2(ps->fd[OUT], OUT) >= 0) || err("dup2")); // && close(fd[OUT]);
		//	ps->pipe[IN] != -1 && ((dup2(ps->fd[IN], IN) >= 0) || err("dup2"));// && close(fd[IN]);
		close_fds(ps->fds);
		if (execve(path, ps->args, environ) == -1)
		{
			(*ps).status &= ~WAIT;
			err("Could not execve"); // todo not exit
		}
	}
	printf("process run...\n");
	return (1);
}

struct process *find_ps_pipe_to(struct process **ps, int pipe_number)
{
	while (*ps)
	{
		if ((**ps).pipe[IN] == pipe_number)
			return (*ps);
		ps++;
	}
	err("fatal");
}

int set_process_fd(struct process *ps, int **fds)
{
	return (1);
}

int handle_processes(struct process **ps)
{
	struct process **tmp;
	int **fds;
	int pipe_number;
	int flag;

	fds = (int**)multalloc(redirs_nbr, 2, sizeof(int));

	tmp = ps;
	while (*ps)
	{
		/* seems that REDIRECT flag not having reason */
		/* seems there is no case when auto read to file */
		/* cases [-1][0] [0][1]
		 * 	 [0] [ 0][1] [1][2]  1 pipe, 2 file
		 **/
		if ((**ps).pipe[OUT] != -1 && !((**ps).file)) //(**ps).status &(W_FILE | A_FILE)))
		{
//			write(1, "pipe ps\n", 8);
			pipe_number = (**ps).pipe[OUT];
			/* pipe() return 0 if success */
			(pipe(fds[pipe_number]) == -1) && err("pipe creation failed");
			(**ps).fd[OUT] = fds[pipe_number][OUT];
			(**ps).fds = fds;
			(*find_ps_pipe_to(tmp, pipe_number)).fd[IN] = fds[pipe_number][IN];
			(*find_ps_pipe_to(tmp, pipe_number)).fds = fds;
		}

		if ((**ps).file)
		{
			//((**ps).status & W_FILE) && (flag = O_WRONLY);
			(flag = O_WRONLY) && ((**ps).status & A_FILE) && (flag |= O_APPEND);
			//((**ps).status & R_FILE) && (flag |= O_RDONLY);
			printf("%d FLAG\n", flag);
			((**ps).fd[OUT] = open((**ps).file, flag));
		}
		(**ps).status |= WAIT;

		//(**ps) & SEQ && ((**ps).status |= WAIT);
		printf("PROCESS (%s,  %s ) PIPE(%d  %d) FD (%d %d) FILE '%s'\n",
			   (*ps)->args[0],
			   (*ps)->args[1],
			   (*ps)->pipe[0],
			   (*ps)->pipe[1],
			   (*ps)->fd[0],
			   (*ps)->fd[1],
			   (*ps)->file);

		create_new_process(*ps);
		//((**ps).status & SEQ) && wait_process(*ps);
		ps++;
	}
	ps = tmp;
	close_fds(fds);
	while (*ps)
	{
		wait_process(*ps);
		ps++;
	}
	return (1);
}

int wait_process(struct process *ps)
{
	int status = 0;

	(*ps).status & WAIT && wait(&status);
	if (WIFEXITED(status))
		/* WIFEXITED True if the process terminated
		 * normally by a call to _exit(2) or exit(3).
		 * If WIFEXITED(status) is true, WEXITSTATUS evaluates to the low-order
		 * 8 bits of the argument passed to _exit(2) or exit(3) by the child. */
		printf("\t\tExit status: %d\n", WEXITSTATUS(status));

	else if (WIFSIGNALED(status))
		/* WIFSIGNALED True if the process terminated
		 * due to receipt of a signal. */
		psignal(WTERMSIG(status), "Exit signal");

	/* status should exist even if */
	last_exit_code = WEXITSTATUS(status);
	/*  free_ps(ps); */
	return (0);
}


int main(void)
{
	write(1, "start\n\n", 7);

	//char *str = ft_strdup("STRING");
	//printf("%s>>\n", str);
	//ft_str_to_lower(str);
	//printf("\n%s<<\n", str);
	//free(str);

#if 1
	struct process **ps;
	ps = (struct process**)multalloc(2, 1, sizeof(struct process));
	if (!ps)
		err("SHIT");
	printf("process number %d\n", arr_len((void**)ps));
//	free(ps[2]);
//	ps[2] = 0;

	//char *args[3] = {"cat", 0, 0};
	//char *args2[3] = {"/bin/cat", "-e", 0};
	//char *args2[3] = {"ls", 0, 0};
	//char *args2[3] = {"/usr/bin/less", 0, 0};
	redirs_nbr = 2;

	ps[0]->args = ft_split("ls", ' ');
	ps[0]->pipe[0] = -1;
	ps[0]->pipe[1] = 0;
	ps[1]->args = ft_split("CAT -e", ' ');
	ps[1]->pipe[0] = 0;
	ps[1]->pipe[1] = -1;
//	ps[1]->file = "text";
//	ps[1]->status |= A_FILE;
	//printf("process number %d\n", arr_len((void**)ps));
	handle_processes(ps);
#endif
}


#if 0

	tst_find_path();

	char **paths = ft_split("", ':');
	while (*paths)
	{
		printf("%s\n", *paths);
		free (*paths);
		paths++;
	}

}
#endif










