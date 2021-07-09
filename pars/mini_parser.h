#ifndef MINI_PARSER_H
# define MINI_PARSER_H

/* # include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
 */
# include "../minishell.h"

/* typedef	struct s_flags
{
	int	single_q;
	int	double_q;
	int	has_pipe;
	int	pipe_in;
	int pipe_out;
	int	pipe_count;
	int	has_env;
	int	back_slash;
	int	has_redir;
	int	double_redir;
	int	double_out;
	int	semi_colon;
	int	out;
	int	red;
}	t_flags; */

typedef	struct s_cmd
{
	char **cmd;
	int				_pipe; // pipe number
	int				pipe[2];
	int				size;
	struct s_cmd	*next;
}	t_cmd;

typedef	struct s_token
{
	char			*token;
	int				c_type;
	int				redir;
	struct s_token	*next;
}	t_token;

typedef	struct s_env
{
	char			*key;
	char			*value;
	int				len;
	struct s_env	*next;
}	t_env;


#endif
