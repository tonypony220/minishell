
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <sys/stat.h>
# include <sysexits.h>
# include <sys/errno.h>
# include <sys/param.h>  /* MAXPATHLEN value */
# include <termcap.h>
# include <readline/readline.h>
# include <readline/history.h>

# define RED 	 "\033[1;31m"
# define GREEN   "\033[0;32m"
# define YELLOW	 "\033[1;33m"
# define BLUE	 "\033[1;34m"
# define PURPLE  "\033[1;35m"
# define CYAN    "\033[1;36m"
# define RESET   "\033[0;0m"
# define BOLD    "\033[;1m"
# define REVERSE "\033[;7m"

# define CMD_NOT_FOUND_CODE 127

# define NO_PIPE -1
# define OUT 1
# define IN 0
# define CHILD_PID 0
# define WAIT 	   1 << 1
# define COMMAND    1 << 2
//# define REDIRECT 1 << 2
//# define W_FILE   1 << 3
//# define R_FILE   1 << 4
# define A_FILE    1 << 5  /* append to dile */
# define SEQ 	   1 << 6	/* process terminates ';'. and not concurent executing */
# define BUILTIN   1 << 7
# define DIRECT    1 << 8  /*  */

# define BUILTINS "env echo pwd export unset exit cd"
# define WR_BUILTINS "env echo pwd"  			/* which write */
# define SELF_BUILTINS "unset exit cd"  	/* which execute */
# define UPPER_BUILTINS "ENV ECHO PWD CD"  		/* which has upper aliases */
# define UPPER_EXCLUDED_BUILTINS "EXPORT UNSET EXIT"  /* which has not upper aliases */
# define SHELL_NAME "minishell"


//struct		vars
//{
//	int		last_exit_code;
//	t_list	*env;
//	struct	process **ps;
////	t_shell *shell;
//};


struct		dict
{
	char	*key;
	char	*value;
};

/* command */
typedef	struct s_cmd
{
	char **cmd;
	int				_pipe; // pipe number
	int				pipe[2];
	int				size;
	struct s_cmd	*next;
}	t_cmd;

/* token */
typedef	struct s_token
{
	char			*token;
	int				redir_type;
	int				redir;
	struct s_token	*next;
}	t_token;

/* FLAGS */
typedef	struct s_flags
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
	int	redir_type;
	int	redir_in;
	int	redir_out;
}	t_flags;

/* T_SHELL */
typedef struct s_shell
{
	t_token		*token;
	t_list			*env;
	//t_env			*env;
	t_list  		*cmd;
	//t_cmd			*cmd;
	t_flags			flags;
	char			**args;
	char			*_arg;
	char			*env_value;
	int				cmd_size;
	int				status;
	int				err;
	int				dq_err;
	int				sq_err;
	int				pipe_err;
	int				redir_err;
	int				arg_size;
	int				env_len;
	int				env_sign;
	int				i;
	int				start;
	int				end;
	int				after_redir;
	int				last_exit_code;
}	t_shell;

struct		process
{
	char	**args;
	int		pipe[2];   /* pipe number ex.: 1 pipe in, 2 pipe out */
				       /* when pipe not used it will be -1 */
	int		fd[2];
	int		**fds; 	   /* all fds inherited from parent process pipe() */
				  	   /* mapping would be pipe number = fds index + 1 */
	int		status;
	int		exit_code; /* reserved unix exit code
	                    * https://tldp.org/LDP/abs/html/exitcodes.html   */
	char	*file;     /* filename to redirections */

	int		redir;		/* 1=redir_in, 2=redit_out, 0=NONE */
	int		redir_type;	/* 1=>> 2=<< 3=< 4=> 0=NONE */

	t_list	*env;	   /* back link on current shell evniron */
	t_shell *shell;	   /* back link on current shell obj */
};

void		ft_str_to_lower(char *str);
int			arr_len(void **p);
int			path_executable(char *name);
char		*find_path(char *name);
void		tst_find_path(void);
int			freemultalloc(void **p);
void		**multalloc(int rows, int columns, unsigned long size);
int			printmultalloc(void **p);
int			wait_process(struct process *ps);
void		print_process(void *ps);

/* execute */
int execute(t_shell *shell);

			/* dict and env functions */
t_list		*get_dict_by_key(t_list *lst, void* (*f)(void *), char* key);
void		del_dict(void* content);
char		*dict_key(void* content);
int			dict_set_default(t_list *lst, char* key, char* value);
struct dict	*new_dict(char *key, char *value);
int			cmp_dict_keys(void* content, void* ref);
void		dict_print(void* content);
char		*dict_value(void* data);

int display_err(struct process *ps);

int			dict_add_back(t_list **env, struct dict *content);
int			upload_env_to_dict(char **envp, t_list **env);
void		env_dict_print(struct dict* content);
char		*env_pull_to_str(struct dict* content);

/* builtins */
int			msh_echo(struct process *ps);
int			msh_export(struct process *ps);
int			msh_unset(struct process *ps);
int			msh_env(struct process *ps);
int			msh_pwd(struct process *ps);
int			msh_cd(struct process *ps);
int			msh_exit(struct process *ps);

void		free_processes(struct process **ps);
void		free_process(struct process *ps, int child);


t_flags		_init_flags(void);
int			_start_shell(t_shell *shell);

/* parser */
int			pre_parser(char *line, t_shell *shell);
void		main_parser(char *line, t_shell *shell, t_token **token);
int			check_cmd(char *line, t_shell *shell);
int			parse_cmd(char *line, t_shell *shell);
int			parse_single_quotes(char *line, t_shell *shell);
int			parse_double_quotes(char *line, t_shell *shell);
int			parse_env_sign(char *line, t_shell *shell);
int			parse_redirect(char *line, t_shell *shell);
int			parse_pipe(char *line, t_shell *shell);

char		*add_env_to_str(char *line, t_shell *shell);
int			check_for_env(char **line, t_shell *shell);
void		free_env_shell(t_shell *shell);

void		set_flags(struct process *new, t_shell *shell);
int			get_env(t_shell *shell, char *line, int i, int end);

/* command */
int			init_command(t_shell *shell);
int			compose_command(t_list **cmds, t_token *token, t_shell *shell);
void		free_command(t_cmd **list);
void		print_command(t_shell *shell);

/* check_cmd */
void	pipe_syntax(char *line, int i, t_shell *shell);
void	redir_syntax(char *line, int i, t_shell *shell);
void	single_quote(char *line, int i, t_shell *shell);
void	double_quote(char *line, int i, t_shell *shell);

/* token */
t_token		*token_lstlast(t_token *lst);
t_token		*token_lstadd(t_token **lst, char *line, t_shell *shell);
int			token_lstsize(t_token *lst);
void		token_lstclear(t_token **list);
char		*token_strjoin(char *rmd, char *buffer);
void		print_token(t_token *token);

/* util */
int			space_skip(const char *nptr, int index);
int			error_out(t_shell *shell, char *error);
void		ft_putendl(char *s, int endl);

#endif
