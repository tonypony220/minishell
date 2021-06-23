#include "minishell.h"

/* commands:
 * cat >> file
 * cat | less file
 * ls | less >> file
 * echo
 * "echo" "strig"
 * "echo" "-n" "strgin"
 */

/*
	bash-3.2$ lss
	bash: lss: command not found
	bash-3.2$ echo $?
	127
	bash-3.2$ ./ssss
	bash: ./ssss: No such file or directory
	bash-3.2$ echo $?
	127
	bash-3.2$ ./seg_ps
	Segmentation fault: 11
	bash-3.2$ echo $?
	139
 */

extern char** environ;

int redirs_nbr;

int	err(char* err_str)

{
	perror(err_str);
	exit(123);
	return 1;  /* don't know how to force return int that compiler accept it*/
}

char *make_err_msg(struct process *ps)
{
	if (ps->exit_code)
		return ("command not found");
	return (strerror(errno));
}

int display_err(struct process *ps)
{
	// todo redirect STD_ERR that errors printed right : )
	//int fd;
	//
	//fd = dup(OUT);
	//dup2(1, 2);
	printf(RED"yosh: %s: %s"RESET"\n", *(ps->args), make_err_msg(ps));
	//dup2();
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

void			dispatching_process(struct process *ps)
{
	char *path;
	char *name;
	char **arr;
	//char *builtins[] = {"env", "echo", "pwd", "export", "unset", "exit"};

	path = ps->args[0];
	/* executable name should be lower case */
	arr = ft_split(UPPER_EXCLUDED_BUILTINS, ' ');
	if (!ft_str_in_strs(path, arr))
		ft_str_to_lower(path);
//	printmultalloc((void**)arr);
	//printf(GREEN"HELLO"RESET"\n");
	freemultalloc((void**)arr);

	arr = ft_split(SELF_BUILTINS, ' ');
	(ft_str_in_strs(path, arr)) && (ps->status |= DIRECT);
//	printmultalloc((void**)arr);
	freemultalloc((void**)arr);

	arr = ft_split(BUILTINS, ' ');
	ft_str_in_strs(path, arr) && (ps->status |= BUILTIN);
//	printmultalloc((void**)arr);
	freemultalloc((void**)arr);

	if (ps->status & BUILTIN)
		return ;

	// todo BUILTINS
	if (path[0] == '/' || path[0] == '.')
		return ;
	if ((name = find_path(ps->args[0])) && (ps->args[0] = name))
		free(path);
	else
		(*ps).exit_code = CMD_NOT_FOUND_CODE;

	(*ps).status |= WAIT;

	printf("'%s' path args '%s' '%s'\n", path, ps->args[0], ps->args[1]);
	// todo how it exits if wrong path
	//!path && err(ft_strjoin(ps->args[0], ": command not found"));
	//ps->args[0] = path;
	//(*ps).status |= WAIT;
}

int			execute_builtin(struct process *ps)
{
	// unset errors with leading numbers or equality sign
	printf("\texecuting command builit %s %s\n",
		   ps->args[0], ps->args[1]);
	ft_strcmp(ps->args[0], "echo") || yosh_echo(ps);
	/// ft_strcmp(ps->args[0], "export") || yosh_export(ps);
	/// ft_strcmp(ps->args[0], "pwd") 	 || yosh_pwd(ps);
	/// ft_strcmp(ps->args[0], "env") 	 || yosh_env(ps);
	/// ft_strcmp(ps->args[0], "exit")   || yosh_exit(ps);
	/// ft_strcmp(ps->args[0], "unset")  || yosh_unset(ps);
	if (!(ps->status & DIRECT))
		exit(ps->exit_code);
}

int			create_new_process(struct process *ps)
{
	/* param fd: waiting only fd to redirect, else 0 */
	int		pid;

	printf("forking process %s %s %s\n", GREEN, ps->args[0], RESET);
	if ((pid = fork()) == -1)
		err("fork failed"); // todo not exit
	else if (pid == CHILD_PID)
	{
		//printf("%s %d %d fds pipe %d %d %d\n",
		//	   ps->args[0], ps->fd[IN], ps->fd[OUT], ps->pipe[IN],
		//	   ps->pipe[OUT], ps->status & BUILTIN);

		/* maybe enough for redirection todo check it */
		ps->fd[OUT] > 2 && ((dup2(ps->fd[OUT], OUT) >= 0) || err("dup2")); // && close(fd[OUT]);
		ps->fd[IN] > 2 && ((dup2(ps->fd[IN], IN) >= 0) || err("dup2"));// && close(fd[IN]);
		/* old version */
		//	ps->pipe[OUT] != -1 && ((dup2(ps->fd[OUT], OUT) >= 0) || err("dup2")); // && close(fd[OUT]);
		//	ps->pipe[IN] != -1 && ((dup2(ps->fd[IN], IN) >= 0) || err("dup2"));// && close(fd[IN]);
		close_fds(ps->fds);
		if (ps->status & BUILTIN)
			execute_builtin(ps);
		if (execve(ps->args[0], ps->args, environ) == -1)
		{
			display_err(ps);
			if (errno == 2)
				exit(127);  //CMD_NOT_FOUND_CODE);
			exit(EXIT_FAILURE);
//			(*ps).status &= ~WAIT; will not affect parent process :(
			//printf(RED"FAILED %s"RESET"\n", ps->args[0]);
			//err(RED"Could not execve"RESET); // todo how memory clears;
		}
	}
	//printf("process ...\n");
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

///int set_process_fd(struct process *ps, int **fds)
///{
///	return (1);
///}

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

		//(**ps) & SEQ && ((**ps).status |= WAIT);

		/* cases to execute directly: exit export unset */
		dispatching_process(*ps);

		printf("PROCESS (%s,  %s) PIPE(%d  %d) FD (%d %d) FILE '%s' BUILTIN:(%d)\n",
			   (*ps)->args[0],
			   (*ps)->args[1],
			   (*ps)->pipe[0],
			   (*ps)->pipe[1],
			   (*ps)->fd[0],
			   (*ps)->fd[1],
			   (*ps)->file,
			   (*ps)->status & BUILTIN && 1);

		if (((*ps)->exit_code) == 0)
		{
			!((*ps)->status & DIRECT) && create_new_process(*ps);
			((*ps)->status & DIRECT) && execute_builtin(*ps);
		}
		//((**ps).status & SEQ) && wait_process(*ps);
		//wait_process(*ps);
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
	int status;
	int exit_code;

	status = 0;
	ps->exit_code || wait(&status);
	//(*ps).status & WAIT &&
	if (WIFEXITED(status))
		/* WIFEXITED True if the process terminated
		 * normally by a call to _exit(2) or exit(3).
		 * If WIFEXITED(status) is true, WEXITSTATUS evaluates to the low-order
		 * 8 bits of the argument passed to _exit(2) or exit(3) by the child. */
		exit_code = WEXITSTATUS(status);
	//	printf("\t\tExit status: %d\n", WEXITSTATUS(status));

	else if (WIFSIGNALED(status))
	{
		//	printf(GREEN"%d"RESET"\n", WIFSIGNALED(status));
		/* WIFSIGNALED True if the process terminated
		 * due to receipt of a signal. */
		//psignal(WTERMSIG(status), "Exit signal");
		exit_code = WTERMSIG(status);
	}
	/* status should exist even if */
	// todo catch status from signaled and put it to last_exit_code
	ps->exit_code && (exit_code = ps->exit_code) && display_err(ps);
	last_exit_code = exit_code;
	//!ps->exit_code && (last_exit_code = exit_code);
	printf("\t\tExit code: %d (%s)\n", last_exit_code , *ps->args);
	/*  free_ps(ps); */
	return (0);
}


int main(int ac, char **av, char **envp)
{
	write(1, "start\n\n", 7);

	//char *str = ft_strdup("STRING");
	//printf("%s>>\n", str);
	//ft_str_to_lower(str);
	//printf("\n%s<<\n", str);
	//free(str);

#if 1
	struct process **ps;
	t_list *env_lst;
	t_list *one;
	struct dict *d;

	env_lst = 0;
	//write(1, "HERE\n", 5);
	upload_env_to_dict(envp, &env_lst);
	//ft_lstiter(env_lst, env_content_print);
	//ft_lstdelone(ft_lstlast(env_lst), del_dict);
	dict_set_default(env_lst, "ONE", "1234");
	dict_set_default(env_lst, "ONE", "1111");
	ft_lstadd_front(&env_lst, ft_lstnew(new_dict(ft_strdup("ONE"), ft_strdup("5555"))));
	ft_lstadd_front(&env_lst, ft_lstnew(new_dict(ft_strdup("ONE"), ft_strdup("5555"))));
	ft_lstiter(env_lst, env_content_print);
	write(1, "\n\n", 2);
	//env_content_print(get_dict_by_key(env_lst, get_key_from_dict, "ONE")->content);
//del_dict_by_key(env_lst, del_dict, dict_key, "PATH");
	//one = get_dict_by_key(env_lst, dict_key, "ONE");
	//one = ft_lst_find(env_lst, (d = new_dict("BO", 0)), cmp_dict_keys);
	free(d);
	ft_lst_rm(&env_lst, (d = new_dict("ONE", 0)), cmp_dict_keys, del_dict);
	free(d);
	ft_lst_rm(&env_lst, (d = new_dict("TERM_PROGRAM", 0)), cmp_dict_keys, del_dict);
	free(d);
	ft_lstiter(env_lst, env_content_print);
	//ft_list_remove_if(env_lst, (d = new_dict("ONE", 0)), cmp_dict_keys, del_dict);
	write(1, "HERE\n", 5);
	free(d);
	if (one)
		env_content_print(one->content);
	else printf(GREEN"nothing"RESET);
	//t_list *found = ft_dictget(env_lst, env_content_get_key, "PATH");
	////printf("%p\n", found);
	//printf("found %s %s\n", ((struct env_dict*)found->content)->key, ((struct env_dict*)found->content)->value);


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

	ps[0]->args = ft_split("echo HELLOLLLLLLL! $?", ' ');
	ps[0]->pipe[0] = -1;
	ps[0]->pipe[1] = 0;
	ps[1]->args = ft_split("CAT -e", ' ');
	//ps[1]->args = ft_split("../sub", ' ');
	ps[1]->pipe[0] = 0;
	ps[1]->pipe[1] = -1;
//	ps[1]->file = "text";
//	ps[1]->status |= A_FILE;
	//printf("process number %d\n", arr_len((void**)ps));
	handle_processes(ps);
#endif

#if 0
// chdir function is declared
// inside this header
	char s[100];
	// printing current working directory
	printf("%s\n", getcwd(s, 100));
	printf("%s\n", getenv("PWD"));

	// using the command
	chdir("..");

	// printing current working directory
	printf("%s\n", getcwd(s, 100));
	printf("%s\n", getenv("PWD"));

	// after chdir is executed
	freemultalloc((void**)ps[0]->args);
	freemultalloc((void**)ps[1]->args);
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

}
#endif

}









