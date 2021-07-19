#include "minishell.h"

int	err(char* err_str)
{
	perror(err_str);
	exit(123);
	return 1;  /* don't know how to force return int that compiler accept it*/
}

/*
 * function calls on getcwd failed as well 
 */
char *make_err_msg(struct process *ps)
{
	if (ps->exit_code)
	{
		if (ps->exit_code == CMD_NOT_FOUND_CODE)
			return ("command not found");
		return (strerror(ps->exit_code));
	}
	return (strerror(errno));
}

int display_err(struct process *ps)
{
	// todo redirect STD_ERR that errors printed right : )
	printf(RED""SHELL_NAME": %s: %s"RESET"\n", *(ps->args), make_err_msg(ps));
	return (1);
}


void		close_fds(int **fds)
{
	while (fds && *fds)
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

	//path = ps->args[0];
	ps->path = ft_strdup(ps->args[0]); //TODO free path
	name = 0;
	/* executable name should be lower case */
	arr = ft_split(UPPER_EXCLUDED_BUILTINS, ' ');
	if (!ft_str_in_strs(ps->path, arr))
		ft_str_to_lower(ps->path);
//	printmultalloc((void**)arr);
	//printf(GREEN"HELLO"RESET"\n");
	freemultalloc((void**)arr);

	arr = ft_split(SELF_BUILTINS, ' ');
	(ft_str_in_strs(ps->path, arr)) && (ps->status |= DIRECT);
//	printmultalloc((void**)arr);
	freemultalloc((void**)arr);

	!ft_strcmp("export", ps->path) && ps->args[1] && (ps->status |= DIRECT);

	arr = ft_split(BUILTINS, ' ');
	ft_str_in_strs(ps->path, arr) && (ps->status |= BUILTIN);
//	printmultalloc((void**)arr);
	freemultalloc((void**)arr);

	if (ps->status & BUILTIN)
		return ;

	// todo BUILTINS
	if (*ps->path == '/' || *ps->path == '.')
		return ;
//	printf("searching path for %s...\n", ps->path);
	//if ((name = find_path(ps->args[0])) && (ps->args[0] = name))
	if ((name = find_path(ps->path)))
	{
		free(ps->path);
		ps->path = name;
	}
	else
	{
		(*ps).exit_code = CMD_NOT_FOUND_CODE;
		display_err(ps);
	}

	(*ps).status |= WAIT;

	//printf("'%s' path args '%s' '%s'\n", path, ps->args[0], ps->args[1]);
	// todo how it exits if wrong path
	//!path && err(ft_strjoin(ps->args[0], ": command not found"));
	//ps->args[0] = path;
	//(*ps).status |= WAIT;
}

int			execute_builtin(struct process *ps)
{
	// unset errors with leading numbers or equality sign
	(ps->status & HEREDOC) && msh_heredoc(ps);
	VERBOSE && printf(CYAN">>executing command builit %s %s\n"RESET, ps->args[0], ps->args[1]);
	ft_strcmp(ps->path, "echo")	  || msh_echo(ps);
	ft_strcmp(ps->path, "export") || msh_export(ps);
	ft_strcmp(ps->path, "pwd") 	  || msh_pwd(ps);
	ft_strcmp(ps->path, "env") 	  || msh_env(ps);
	ft_strcmp(ps->path, "exit")   || msh_exit(ps);
	ft_strcmp(ps->path, "cd")	  || msh_cd(ps);
	ft_strcmp(ps->path, "unset")  || msh_unset(ps);
	if (!(ps->status & DIRECT))
		exit(ps->exit_code);
	return (0);
}

/* It's not strighforward way to detect leaks in child process,
 * so to save time those are won't be hadleled.
 * Closing fds is reuquired, cause pipes waits for closing 
 * all it's end or EOF */
int			create_new_process(struct process *ps)
{
	int		pid;
//	char	*exec_path;

////////////	printf(CYAN">>forking process %s %s %s\n"RESET, GREEN, ps->args[0], RESET);

	if ((pid = fork()) == -1) // todo why fork creates several leaks ????
		err("fork failed"); // todo not exit
	else if (pid == CHILD_PID)
	{
		//printf("%s %d %d fds pipe %d %d %d\n",
		//	   ps->args[0], ps->fd[IN], ps->fd[OUT], ps->pipe[IN],
		//	   ps->pipe[OUT], ps->status & BUILTIN);

		/* maybe enough for redirection todo check it */
		ps->fd[OUT] > 2 && ((dup2(ps->fd[OUT], OUT) >= 0) || err("dup2")); //&& close(ps->fd[OUT]);
		ps->fd[IN] > 2 && ((dup2(ps->fd[IN], IN) >= 0) || err("dup2")); //&& close(ps->fd[IN]);
		/* old version */
		//	ps->pipe[OUT] != -1 && ((dup2(ps->fd[OUT], OUT) >= 0) || err("dup2")); // && close(fd[OUT]);
		//	ps->pipe[IN] != -1 && ((dup2(ps->fd[IN], IN) >= 0) || err("dup2"));// && close(fd[IN]);
		//write(1, "WTF<<\n", 6);
		//printf("%p fds\n", ps->fds);
		close_fds(ps->fds);
	//	close(ps->fd[IN]);
	//	close(ps->fd[OUT]);
		ps->file[IN] && close(ps->fd[IN]);
		ps->file[OUT] && close(ps->fd[OUT]);
	//	if (ps->status & HEREDOC) /* HEREDOC */
	//		exec_heredoc(ps);
//		if (ps->redir) /* redirection */
//			check_for_redir(ps);
		if (ps->status & BUILTIN)
			execute_builtin(ps);
		//ft_lstiter(ps->env, dict_print);
	//	char **envv = 0;
	//	envv = ft_lst_to_strs(ps->env, dict_to_str);
	//	printmultalloc((void**)environ);	
	//	printf("\n\n");
	//	printf("%p<<<\n", *envv);
		//printmultalloc((void**)envv);	
		//printf("%p<<<\n", *envv); envv
	///	exec_path = ps->path;
	///	exec_path || (exec_path = ps->args[0]);
		//printf("%s %s <<<\n", ps->path, ps->args[0], ps->args[1]);
		execve(ps->path, ps->args, ft_lst_to_strs(ps->env, dict_to_str)); // no alloc check
	//	execve(ps->args[0], ps->args, environ);
		display_err(ps);
		if (errno == 2)
			exit(127);  //CMD_NOT_FOUND_CODE);
		exit(EXIT_FAILURE);

//			(*ps).status &= ~WAIT; will not affect parent process :(
		//printf(RED"FAILED %s"RESET"\n", ps->args[0]);
		//err(RED"Could not execve"RESET); // todo how memory clears;
	}
	//printf("process ...\n");
	return (1);
}

//struct process *find_ps_pipe_to(struct process **ps, int pipe_number)
//{
//	while (*ps)
//	{
//		if ((**ps).pipe[IN] == pipe_number)
//			return (*ps);
//		ps++;
//	}
//	err("fatal");
//}

///int set_process_fd(struct process *ps, int **fds)
///{
///	return (1);
///}
//
//
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
//	while ((filename = (ft_lstgen(ps->files_in, get_filename))))
//		printf("%s ", filename);
	printf("\nFILES OUT: ");
	ft_lstiter(ps->files_out, pr);
//	while ((filename = (ft_lstgen(ps->files_out, get_filename))))
//		printf("'s%p ", filename);

	printf("\nBUILTIN:(%d) DIRECT:(%d) REDIRECT=%d, HEREDOC=%d)\n"RESET,
		   ps->status & BUILTIN && 1,
		   ps->status & DIRECT && 1,
		   ps->status & A_FILE && 1,
		   ps->status & HEREDOC && 1
		   );
}

//int get_fileno(struct process *ps)
//{
//	if (((*ps).status & R_FILE))
//		return (IN);
//	return (OUT);
//}

//int get_open_file_flag(struct process *ps, int *flag)
//{
////	printf("%d RFILE flag %d \n", (*ps).status & R_FILE, O_RDONLY);
//	if (((*ps).status & R_FILE) && !(*flag = O_RDONLY))
//		return (IN);
//	*flag = O_WRONLY | O_CREAT;
//	((*ps).status & A_FILE) && (*flag |= O_APPEND);
//	!((*ps).status & A_FILE) && (*flag |= O_TRUNC);
//	return (OUT);
//}
char					*get_filename(void* data)
{
	//printf("%p < data\n", data);
	return ((char*)data);
}

void start_process(void *proc)
{
	struct process *ps;
	int pipe_number;
	int i;
	int flag;
	char *filename;

	//printf("process starting...\n");
	ps = (struct process*)proc;
	/* 	 seems that REDIRECT flag not having reason 
	 * 	 seems there is no case when auto read to file 
	 * 	 cases [-1][0] [0][1]
	 * 	   [0] [ 0][1] [1][2]  1 pipe, 2 file
	 */
	//(*ps).env = env;
	if ((!ps->args[0]) && (ps->status |= SKIP))  // TODO no args also should enter aborting next 
		return ;
	if (ps->pipe[IN] != NO_PIPE)
	{
		pipe_number = (*ps).pipe[IN];
		ps->fd[IN] = ps->fds[pipe_number][IN];
	}
	if ((*ps).pipe[OUT] != NO_PIPE)// && !((*ps).file)) //(**ps).status &(W_FILE | A_FILE)))
	{
		pipe_number = (*ps).pipe[OUT];
		/* pipe() return 0 if success */
		(pipe(ps->fds[pipe_number]) == -1) && err("pipe creation failed");
		ps->fd[OUT] = ps->fds[pipe_number][OUT];
		//(*ps).fds = fds;
	//	(*find_ps_pipe_to(tmp, pipe_number)).fd[IN] = fds[pipe_number][IN];
	//	(*find_ps_pipe_to(tmp, pipe_number)).fds = fds;
	}
	i = 0;
	while ((filename = (ft_lstgen(ps->files_in, get_filename))))
	{
		(*ps).fd[IN] && close((*ps).fd[IN]);
		((*ps).fd[IN] = open(filename, O_RDONLY, 0644));
		if ((*ps).fd[IN] == -1 
//		 && (*ps->flag = ABORT_CODE)
		 && (ps->status |= SKIP)
		 && display_err(ps))
			return ;
		ps->file[IN] = filename;
		//free(ps->file[IN]);
	}
////	if ((*ps).file[IN])
////	{
////		//((**ps).status & W_FILE) && (flag = O_WRONLY);
////		//flag = O_WRONLY;
////		//((*ps).status & R_FILE) && (flag = O_RDONLY);
////		//(flag & O_WRONLY) && (flag |= O_CREATE);
////		//(flag & O_WRONLY) && ((*ps).status & A_FILE) && (flag |= O_APPEND);
////														/* O_TRUNC for > to file to clear it */
////		//((**ps).status & R_FILE) && (flag |= O_RDONLY);
////		//get_open_file_flag(ps, &flag);
////		//printf("%d FLAG std %d\n", flag, std);
////		((*ps).fd[IN] = open((*ps).file[IN], O_RDONLY, 0644));
////	}
////	i = 0;

	while ((filename = (ft_lstgen(ps->files_out, get_filename))))
	{

		(*ps).fd[OUT] && close((*ps).fd[OUT]);
		flag = O_WRONLY | O_CREAT;
		((*ps).status & A_FILE) && (flag |= O_APPEND);
		!((*ps).status & A_FILE) && (flag |= O_TRUNC);
		((*ps).fd[OUT] = open(filename, flag, 0644));
		if ((*ps).fd[OUT] == -1 
//			&& (*ps->flag = ABORT_CODE)
			&& (ps->status |= SKIP)
			&& display_err(ps))
			return ;
		ps->file[OUT] = filename;
		//free(ps->file[IN]);
		/* errors: opening sys files or commands */
	}
////	if (ps->file[OUT])
////	{
////		flag = O_WRONLY | O_CREAT;
////		((*ps).status & A_FILE) && (flag |= O_APPEND);
////		!((*ps).status & A_FILE) && (flag |= O_TRUNC);
////		((*ps).fd[OUT] = open((*ps).file[OUT], flag, 0644));
////	}

	//(**ps) & SEQ && ((**ps).status |= WAIT);

	/* cases to execute directly: exit export unset */
	dispatching_process(ps);

	print_process(ps);

	if (((*ps).exit_code) == 0)
	{
		!((*ps).status & DIRECT) && create_new_process(ps);
		((*ps).status & DIRECT) && execute_builtin(ps);
	}
	//((**ps).status & SEQ) && wait_process(*ps);
	//wait_process(*ps);
	//ps++;
}

void end_process(void *proc)
{
	struct process *ps;

//	printf("process waiting...\n");
	ps = (struct process*)proc;
//	if ((*ps).file) /* auxillaty close */
//	{
//j	close(ps->fd[IN]);
//j	close(ps->fd[OUT]);
	(*ps).file[OUT] && close((*ps).fd[OUT]);
	(*ps).file[IN] && close((*ps).fd[IN]);
//	}
	(ps->status & SKIP) && (ps->shell->last_exit_code = 1);
	(ps->status & SKIP) || wait_process(ps);
	//free_process(ps, 0); /* TODO */
}

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
//void set_shell_to_ps(void *proc, void *shell)
//{
//	struct process *ps;
//
//	ps = (struct process*)proc;
//	ps->shell = shell;
//}
//
//void set_env_to_ps(void *proc, void *env)
//{
//	struct process *ps;
//
//	ps = (struct process*)proc;
//	ps->env = env;
//}

void count_redirections(void *proc, void *redirs)
{
	struct process *ps;

	ps = (struct process*)proc;
	if ((*ps).pipe[OUT] != NO_PIPE)		
		*(int*)redirs += 1;
}

int handle_processes(t_list *cmd, t_list *env)
{
	int redirs;
	int **fds;
	int flag;

	fds = 0;
	flag = 0;
	redirs = 0;
	ft_lstiter_arg(cmd, count_redirections, &redirs);
	VERBOSE && printf("start hadnling cmds... %d pipes <<\n", redirs);
	redirs && (fds = (int**)multalloc(redirs, 0, sizeof(int)));
	ft_lstiter_arg(cmd, set_fds_to_ps, fds);
	ft_lstiter_arg(cmd, set_flag_to_ps, &flag);
	ft_lstiter(cmd, start_process);
	close_fds(fds);
	freemultalloc((void**)fds);
	/* should let iter on error to free memory*/ 
	ft_lstiter(cmd, end_process);
	//ft_lstclear(&((struct process*)cmd->content)->shell->cmd, free_process);
	return (1);
}

int wait_process(struct process *ps)
{
	int status;
	int exit_code;

	status = 0;
	ps->exit_code || (ps->status & DIRECT) || wait(&status);
	//(*ps).status & WAIT &&
	if (WIFEXITED(status))
		/* WIFEXITED True if the process terminated
		 * normally by a call to _exit(2) or exit(3).
		 * If WIFEXITED(status) is true, WEXITSTATUS evaluates to the low-order
		 * 8 bits of the argument passed to _exit(2) or exit(3) by the child. */
		exit_code = WEXITSTATUS(status);
	//	printf("\t\tExit status: %d\n", WEXITSTATUS(status));

	if (WIFSIGNALED(status))
	{
		//	printf(GREEN"%d"RESET"\n", WIFSIGNALED(status));
		
		/* WIFSIGNALED True if the process terminated
		 * due to receipt of a signal. */
	//	psignal(WTERMSIG(status), "Exit signal");
		write(1, "\r", 1);
		exit_code = WTERMSIG(status) + 128;
	}

	//printf("\t\texit code: %d (%s)\n", exit_code , *ps->args);

	/* status should exist even if */
	// todo catch status from signaled and put it to last_exit_code
	exit_code && (ps->exit_code = exit_code);
	ps->exit_code && (exit_code = ps->exit_code);
	//// (ps->exit_code == CMD_NOT_FOUND_CODE) && display_err(ps);
	ps->shell->last_exit_code = exit_code;
	//!ps->exit_code && (last_exit_code = exit_code);
	
	VERBOSE && printf(CYAN"\t\tExit code: %d (%s)"RESET"\n", ps->shell->last_exit_code , *ps->args);
	return (0);
}

int execute(t_shell *shell)
{
	handle_processes(shell->cmd, shell->env);
}

int __main(int ac, char **av, char **envp)
{
	//write(1, "start\n\n", 7);

	//char *str = ft_strdup("STRING");
	//printf("%s>>\n", str);
	//ft_str_to_lower(str);
	//printf("\n%s<<\n", str);
	//free(str);

	//struct process **ps;
	t_list *cmd;
	t_list *env_lst;
	t_list *one;
	struct dict *d = 0;
	struct process *ps;


	ps = 0;
	cmd = 0;
	env_lst = 0;
	//write(1, "HERE\n", 5);
	upload_env_to_dict(envp, &env_lst);
	//ft_lstiter(env_lst, dict_print);
#if 0
	//ft_lstdelone(ft_lstlast(env_lst), del_dict);
	dict_set_default(env_lst, ft_strdup("ONE"), ft_strdup("1234"));
	write(1, "HERE\n", 5);
	dict_set_default(env_lst, ft_strdup("ONE"), ft_strdup("2222"));
	//ft_lstadd_front(&env_lst, ft_lstnew(new_dict(ft_strdup("ONE"), ft_strdup("5555"))));
	//ft_lstadd_front(&env_lst, ft_lstnew(new_dict(ft_strdup("ONE"), ft_strdup("5555"))));
	//ft_lstiter(env_lst, dict_print);
	write(1, "\n\n", 2);
	//dict_print(get_dict_by_key(env_lst, get_key_from_dict, "ONE")->content);
//del_dict_by_key(env_lst, del_dict, dict_key, "PATH");
	//one = get_dict_by_key(env_lst, dict_key, "ONE");
	//one = ft_lst_find(env_lst, (d = new_dict("BO", 0)), cmp_dict_keys);
	
	//// free(d);
	//// ft_lst_rm(&env_lst, (d = new_dict("ONE", 0)), cmp_dict_keys, del_dict);
	//// free(d);
	//// ft_lst_rm(&env_lst, (d = new_dict("TERM_PROGRAM", 0)), cmp_dict_keys, del_dict);
	//// free(d);
	//// ft_lstiter(env_lst, dict_print);
	//ft_list_remove_if(env_lst, (d = new_dict("ONE", 0)), cmp_dict_keys, del_dict);
	write(1, "HERE\n", 5);
	//if (one)
	//	dict_print(one->content);
	//else printf(GREEN"nothing"RESET);
	//t_list *found = ft_dictget(env_lst, env_content_get_key, "PATH");
	////printf("%p\n", found);
	//printf("found %s %s\n", ((struct env_dict*)found->content)->key, ((struct env_dict*)found->content)->value);


	ps = (struct process**)multalloc(3, 1, sizeof(struct process));
	if (!ps)
		err("SHIT");
	//printf("process number %d\n", arr_len((void**)ps));
//	free(ps[2]);
//	ps[2] = 0;

	//char *args[3] = {"cat", 0, 0};
	//char *args2[3] = {"/bin/cat", "-e", 0};
	//char *args2[3] = {"ls", 0, 0};
	//char *args2[3] = {"/usr/bin/less", 0, 0};
	redirs_nbr = 0;

	ps[0]->args = ft_split("pwd", ' ');
	ps[0]->pipe[0] = NO_PIPE;
	ps[0]->pipe[1] = NO_PIPE;

	ps[1]->args = ft_split("cd ..", ' ');
	ps[1]->pipe[0] = NO_PIPE;
	ps[1]->pipe[1] = NO_PIPE;

	ps[2]->args = ft_split("echo $?", ' ');
	ps[2]->pipe[0] = NO_PIPE;
	ps[2]->pipe[1] = NO_PIPE;
//	ps[1]->file = "text";
//	ps[1]->status |= A_FILE;
	//printf("process number %d\n", arr_len((void**)ps));
	handle_processes(ps, env_lst);
#endif
#if 1
//	ps = (struct process**)multalloc(1, 1, sizeof(struct process));
//	if (!ps)
//		err("SHIT");
	//printf("process number %d\n", arr_len((void**)ps));
//	free(ps[2]);
//	ps[2] = 0;

	//char *args[3] = {"cat", 0, 0};
	//char *args2[3] = {"/bin/cat", "-e", 0};
	//char *args2[3] = {"ls", 0, 0};
	//char *args2[3] = {"/usr/bin/less", 0, 0};
	redirs_nbr = 0;

	ps = ft_calloc(1, sizeof(struct process));
	ps->args = ft_split("cat ttt", ' ');
	ps->pipe[IN] = NO_PIPE;
	ps->pipe[OUT] = NO_PIPE;
	ps->env = env_lst;
	ft_lstadd_front(&cmd, ft_lstnew(ps));

	//ft_lstadd_front(&env_lst, ft_lstnew(new_dict(ft_strdup("ONE"), ft_strdup("5555"))));
	//
//	ps[1]->args = ft_split("cat", ' ');
	//ps[1]->args = ft_split("../sub", ' ');
//	ps[1]->pipe[IN] = NO_PIPE;
//	ps[1]->pipe[OUT] = NO_PIPE;
//	ps[1]->file = "text";

	//ps[2]->args = ft_split("cat -e", ' ');
	//ps[1]->pipe[IN] = 1;
	//ps[1]->pipe[OUT] = -1;
//	ps[1]->status |= A_FILE;
	//printf("process number %d\n", arr_len((void**)ps));
	handle_processes(cmd, env_lst);

	//free(ps);
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









