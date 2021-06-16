#include "mini_parser.h"

#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **lsh_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

void	single_quote(char *line, int i, t_shell *shell)
{
	int j;

	j = i;
	while(line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			shell->sq_err = 1;
			i++;
			while (line[i] != '\0')
			{
				if (line[i] == '\'')
				{
					shell->sq_err = 0;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	if (shell->sq_err == 1)
		error_out(shell, "syntax error single quotes");
}

void	double_quote(char *line, int i, t_shell *shell)
{
	int j;

	j = i;
	while(line[i] != '\0') //kkkk'kkkekekekeke
	{
		if (line[i] == '\"')
		{
			shell->dq_err = 1;
			i++;
			while (line[i] != '\0')
			{
				if (line[i] == '\"')
				{
					shell->dq_err = 0;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	if (shell->dq_err == 1)
		error_out(shell, "syntax error double quotes");
}

int		check_cmd(char *line, int *i, t_shell *shell)
{
	int j;
	char qq;

	j = *i;
	single_quote(line, j, shell);
	double_quote(line, j, shell);
	shell->dq_err = 0;
	shell->sq_err = 0;
	*i = j;
	if (shell->err == -1)
		return (-1);
	return (1);
}

void	print_cmd(t_shell *shell)
{
	while (shell->cmd)
	{
		ft_putendl(shell->cmd->cmd, 1);
		shell->cmd = shell->cmd->next;
	}
}

/* void	print_cmd(t_list *cmd)
{
	while (cmd)
	{
		ft_putendl(cmd->cmd, 1);
		cmd = cmd->next;
	}
} */

t_list	*parse_cmd(char *line, int *i, t_shell *shell)
{
	int j;
	int end;
	t_list *cmd;

	cmd = NULL;
	j = *i;
	//printf("%s\n", line);
	//printf("[%c]\n", line[j]);
	while (line[*i] != '\0')
	{
		if (line[*i] == ' ' || line[*i + 1] == '\0' || line[*i] == '\'' 
				|| line[*i] == '\"' || line[*i] == '\\')
		{
			space_skip(line, i);
			end = *i;
			if (line[*i + 1] == '\0')
				end++;
			//ft_putendl("YA TYT", 1);
			printf("[%c-%c]\n", line[j], line[end]);
			ft_lstadd(&cmd, line, j, end);
			if (line[*i] == '\'' || line[*i] == '\"' || line[*i] == '\\')
			{
				(*i)--;
				break ;
			}
			j = end++;
		}
		(*i)++;
	}
	return (cmd);
}

/* t_list	*parse_cmd(char *line, int *i, t_shell *shell)
{
	int j;
	int end;
	t_list *cmd;

	cmd = NULL;
	j = *i;
	while (line[*i] != '\0')
	{
		while (line[*i] != ' ')
		{
			//printf("%c\n", line[*i]);
			//space_skip(line, i);
			end = *i;
			if (line[*i + 1] == '\0')
				end++;
			//ft_putendl("YA TYT", 1);
			//printf("[%c-%c]\n", line[j], line[end]);
			ft_lstadd(&cmd, line, j, end);
			j = end++;
		}
		(*i)++;
	}
	return (cmd);
} */

/* t_list	*parse_to_list(char *line)
{
	t_list	cmd;

	cmd = NULL;
} */

t_list	*parse_double_quotes(char *line, int *i, t_shell *shell)
{
	int j;
	int end;
	t_list *cmd;

	cmd = NULL;
	(*i)++;
	j = *i;
	while (line[*i] != '\0')
	{
		if (line[*i] == '\"')
		{
			end = (*i);
			//ft_putendl("YA TYT", 1);
			//printf("[%c - %c]\n", line[j], line[end]);
			ft_lstadd(&cmd, line, j, end);
			break ;
		}
		(*i)++;
	}
	return (cmd);
}

t_list	*parse_single_quotes(char *line, int *i, t_shell *shell)
{
	int j;
	int end;
	t_list *cmd;

	cmd = NULL;
	j = *i;
	//printf("%c\n", line[*i]);
	while (line[*i] != '\0')
	{
		if (line[*i] == '\'' || line[*i + 1] == '\0')
		{
			end = *i;
			if (line[*i + 1] == '\0')
				end++;
			//ft_putendl("YA TYT", 1);
			//printf("[%c-%c]\n", line[j], line[end]);
			ft_lstadd(&cmd, line, j, end);
			j = end++;
		}
		(*i)++;
	}
	return (cmd);
}

int			mini_parser(char *line, t_shell *shell)
{
	int i;
	t_list	*cmd;

	i = 0;
	cmd = NULL;
	space_skip(line, &i);
	if (line[i] == ';' || line[i] == '|')
		return (error_out(shell, "syntax error near unexpected token")); // ';' or '|'
	if (check_cmd(line, &i, shell) < 1) //check for syntax errors
		return (-1);
	//cmd = parse_cmd(line, &i, shell);
	while(line[i] != '\0')
	{
		if (line[i] == '\'')
			cmd = parse_single_quotes(line, &i, shell);
		if (line[i] == '\"')
			cmd = parse_double_quotes(line, &i, shell);
/* 		if (line[i] == '\\')
			parse_back_slash(line, &i, shell);
		if (line[i] == '$')
			parse_env_sign(line, &i, shell);
		if (line[i] == '>' || line[i] == '>>' || line[i] == '<')
			parse_redirect(line, &i, shell);
		if (line[i] == '|' || line[i] == ';')
			parse_pipe_and_semicolon(line, &i, shell);
		else
			parse_cmd(line, &i, shell); */
		//ft_putendl("YA TYT", 1);
		//printf("%c\n", line[i]);
/* 		if (line[i] == '\'')
		{
			ft_putendl("LOL", 1);
			break ;
		} */
		else
			cmd = parse_cmd(line, &i, shell);
		if (line[i] == '\0')
			break ;
		i++;
	}
	if (cmd == NULL)
		return (0);
	shell->cmd = cmd;
	print_cmd(shell);
	ft_lstclear(&shell->cmd);
	return (1);
}

/* int	mini_exec(char **line, t_shell *shell)
{
	pid_t pid, wpid;
	int status;

	if (line[0] == NULL)
		return (1);
	pid = fork();
	if (pid == 0) // Child process
	{
		printf("input->[%s | %s]\n", line[0], line[0]);
		if (execvp(line[0], line) == -1) // change to execve
			perror("MINISHELL");
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
} */

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

int		start_shell(t_shell *shell)
{
	char *line;

	shell->status = 1;
	while (shell->status)
	{
		//find_pwd(); to find and store pwd in string to display in prompt
		ft_putendl("[minishell(%%s)]# ", 0); // %s for pwd path
		get_next_line(0, &line);
		shell->err = 0;
		//printf("%s\n", line);
		if (ft_strncmp(line, "vihod", 5) == 0)
			shell->status = 0;
		mini_parser(line, shell);
		//mini_cmd(shell);
		//ft_putendl(shell->cmd.cmd, 1);
		//mini_exec(&line, shell);
		//print_cmd(shell);
		//if (ft_strncmp(shell->cmd->cmd, "exit", 4) == 0)
		//		shell->status = 0;
		free(line);
		//free(shell->cmd.cmd);
		//ft_lstclear(&shell->cmd);
	}
	return (1);
}

t_par	init_pars(void)
{
	t_par	pars;

	pars.semi_colon = 1;
	pars.back_slash = 0;
	pars.single_q = 0;
	pars.double_q = 0;
	pars.has_env = 0;
	pars.has_pipe = 0;
	pars.has_redir = 0;
	pars.double_redir = 0;
	pars.pipe_count = 0;
	return (pars);
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	t_par	pars;
	//t_list	*cmd;

	//cmd->cmd = NULL;
	//cmd = NULL;
	//cmd->i = 0;
	shell.pars = init_pars();
	shell.err = 0;
	shell.sq_err = 0;
	shell.dq_err = 0;
	system("clear");
	start_shell(&shell);
	return (0);
}