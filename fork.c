#include "minishell.h"

/* commands:
 * cat >> file
 * cat | less file
 * ls | less >> file
 * echo 
 */

extern char** environ;

int last_exit_code;
int pipes_number;

int	err(char* err_str)
{
	perror(err_str);
	exit(1);
	return 1;
}

int		new_process(char **args, int fd[2])
{
	/* param fd: waiting only fd to redirect, else 0 */

	int	pid, wpid;
	int status;
	char *path;

	//printf("pid %d %d\n", getpid(), 0);
	
	//!dup2(fd[1], 1) || err("dup");

	if ((pid = fork()) == -1)
	{
		perror("demo");
		exit(1);
	}
	else if (pid == CHILD_PID)
	{
		path = find_path(ps->args[0]);
		!path && err(ft_strjoin(ps-args[0], ": command not found"));
//  	printf("parent pid %d getpid %d getppid %d\n", pid, getpid(), getppid());
//
//		fd[OUT] = open("text", O_WRONLY | O_APPEND);
//		int d = dup2(fd[1], 1);
//		printf("%d<<\n", d);
//	
		printf("%d %d fds\n", fd[IN], fd[OUT]);

		fd[OUT] && ((dup2(fd[OUT], OUT) >= 0) || err("dup2")) && close(fd[OUT]);   	
		fd[IN] && ((dup2(fd[IN], IN) >= 0) || err("dup2")) && close(fd[IN]);   	

		if (execve(path, args, environ) == -1)
            err("Could not execve");
	}

	else 					/* parent pid = child pid */

	return 1;
}

int **multi_alloc(int rows, int columns)
{
// todo exiting process when allocation fails

	int** x;
	int i;

	x = malloc (sizeof (int*) * rows + 1);
	!x && err("shit");
	x[rows] = 0;

	i = -1;
	while (++i < rows)
	{
		x[i] = malloc(sizeof(int) * columns);
		!x[i] && err("shit");
	}
}

struct process *find_ps_pipe_to(struct process **ps, int pipe_number)
{
	while (*ps)
	{
		if ((**ps).pipe[IN] == pipe_number))
			return (*ps);
		ps++;
	}
	err("fatal");
}

int handle_processes(struct process **ps)
{
	struct process **tmp;
	int **fds;

	fds = multi_alloc(pipes_number, 2);
	fds -= 1; /* number <> index mapping */

	tmp = ps;
	while (*ps)
	{
		if ((**ps).pipe[OUT] && !(**ps).file)
		{
			int pipe_number = (**ps).pipe[OUT];
			/* pipe() return 0 if success */
			(pipe(fds[pipe_number]) == -1) && err("pipe creation failed");
			(**ps).fd[OUT] = fds[pipe_number][OUT];
			(**ps).fds = fds + 1;
			(*find_ps_pipe_to(tmp, pipe_number)).fd[IN] = fds[pipe_number][IN];
			(*find_ps_pipe_to(tmp, pipe_number)).fds = fds + 1;
		}
		else if (ps.status & REDIRECT)

		new_process(*ps);
		close(fd[0]);
		ps++;
	}
	ps = tmp;
	while (*ps)
	{
		ps.status & WAIT && wait(&status);
		if (WIFEXITED(status))
			/* WIFEXITED True if the process terminated
			 * normally by a call to _exit(2) or exit(3).
			 * If WIFEXITED(status) is true, WEXITSTATUS evaluates to the low-order
			 * 8 bits of the argument passed to _exit(2) or exit(3) by the child. */
			printf("Exit status: %d\n", WEXITSTATUS(status));

		else if (WIFSIGNALED(status))
			/* WIFSIGNALED True if the process terminated
			 * due to receipt of a signal. */
			psignal(WTERMSIG(status), "Exit signal");

		/* status should exist even if */
		last_exit_code = WEXITSTATUS(status);
		ps++;
		/*  free(proc); */
	}
	return (1);
}

int main(void)
{

	char *line;
//    char **args;
	int status;

//	while (status)
//    printf("> ");
//    line = lsh_read_line();
//    args = lsh_split_line(line);
//    status = lsh_execute(args);
//
//    free(line);
//    free(args);

	char *args[3] = {"/bin/cat", "text", 0};
	char *args2[3] = {"/usr/bin/less", 0, 0};
	int fd[2] = {0, 0};
//	fd[OUT] = open("text", O_WRONLY | O_APPEND);

	/* pipe() return 0 if success */
	(pipe(fd) == -1) && err("pipe creation failed");

	//printf("fds %d\n", fd[OUT], fd[IN]);

#if 1
	new_process(args, fd);
	close(fd[1]);

	new_process(args2, fd2);
	close(fd[0]);
	wait(&status);
	wait(NULL);
#endif



#if 0

	tst_find_path();

	char **paths = ft_split("", ':');
	while (*paths)
	{
		printf("%s\n", *paths);
		free (*paths);
		paths++;
	}

#endif
}











