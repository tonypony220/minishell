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
# define ABORT_CODE -1

# define NO_PIPE -1
# define OUT 1
# define IN 0
# define CHILD_PID 0
# define WAIT 	    2
# define COMMAND    4
/* calls when bash executes << redirection. we not call it */
# define HEREDOC    8
/* read from file */
# define R_FILE     16
/* append to file */
# define A_FILE     32
/* process terminates ';'. and not concurent executing */
# define SEQ 	    64
# define BUILTIN    128
# define DIRECT     256
# define SKIP     	512
# define ONLY_FILE  1024

# define BUILTINS "env echo pwd export unset exit cd"
/* which write */
# define WR_BUILTINS "env echo pwd"
/* which execute */
# define SELF_BUILTINS "unset exit cd"
/* which has upper aliases */
# define UPPER_BUILTINS "ENV ECHO PWD CD"
/* which has not upper aliases */
# define UPPER_EXCLUDED_BUILTINS "EXPORT UNSET EXIT"
# define SHELL_NAME "minishell"

# define DBL_TO	  1
# define DBL_FROM 2
# define ONE_FROM 3
# define ONE_TO   4

# define VERBOSE 0

struct		s_dict
{
	char	*key;
	char	*value;
};

/* command */
typedef struct s_cmd
{
	char			**cmd;
	int				_pipe;
	int				pipe[2];
	int				size;
	struct s_cmd	*next;
}	t_cmd;

/* token */
typedef struct s_token
{
	char			*token;
	int				redir_type;
	int				redir;
	struct s_token	*next;
}	t_token;

/* FLAGS */
typedef struct s_flags
{
	int			single_q;
	int			double_q;
	int			has_pipe;
	int			pipe_in;
	int			pipe_out;
	int			pipe_count;
	int			has_env;
	int			back_slash;
	int			has_redir;
	int			redir_type;
	int			redir_in;
	int			redir_out;
	int			heredoc;
}	t_flags;

/* T_SHELL */
typedef struct s_shell
{
	t_token		*token;
	t_list		*env;
	t_list		*cmd;
	t_flags		flags;
	t_token		*files;
	char		**args;
	char		*_arg;
	char		*line;
	char		*env_value;
	char		*heredoc;
	int			hd_cnt;
	int			in_compose;
	int			status;
	int			err;
	char		*err_msg;
	int			dq_err;
	int			sq_err;
	int			pipe_err;
	int			redir_err;
	int			arg_size;
	int			env_len;
	int			env_sign;
	int			_env_exit;
	int			redir_count;
	int			i;
	int			st;
	int			end;
	int			after_redir;
	int			last_exit_code;
}	t_shell;

/* pipe: 	  number ex.: 1 pipe in, 2 pipe out */
/* 		 	  when pipe not used it will be -1 */

/* fds: 	  all fds inherited from parent process pipe() */
/* 			  mapping would be pipe number = fds index + 1 */

/* exit_code: reserved unix exit code
			  https://tldp.org/LDP/abs/html/exitcodes.html   */

/* env:		  back link on current shell evniron */
/* shell:	  back link on current shell obj */
struct			s_process
{
	char		**args;
	char		*path;
	int			pipe[2];
	int			fd[2];
	int			**fds;
	int			status;
	int			exit_code;
	char		*file[2];
	t_list		*files_in;
	t_list		*files_out;
	int			*flag;
	t_list		*env;
	t_shell		*shell;
};

void			*get_filename(void *data);
/* global status */

int				create_new_process(struct s_process *ps);
int				execute_builtin(struct s_process *ps);
int				handle_processes(t_list *cmd);
void			ft_str_to_lower(char *str);
int				arr_len(void **p);
int				path_executable(char *name);
char			*find_path(char *name);
void			tst_find_path(void);
int				freemultalloc(void **p);
void			**multalloc(int rows, int columns, unsigned long size);
int				printmultalloc(void **p);
int				wait_process(struct s_process *ps);
void			print_process(void *ps);

void			start_process(void *proc);
int				files_in_redirects(struct s_process *ps);
int				files_out_redirects(struct s_process *ps);

void			dispatching_process(struct s_process *ps);
void			dispatch_status(struct s_process *ps);

void			set_flag_to_ps(void *proc, void *flag);
void			set_fds_to_ps(void *proc, void *fds);
void			pr(void *data);
int				err(char *err_str);
void			close_fds(int **fds);
/* execute */
<<<<<<< HEAD
int				execute(t_shell *shell);

				/* dict and env functions */
t_list			*get_dict_by_key(t_list *lst, void *(*f)(void *), char *key);
void			del_dict(void *content);
char			*dict_key(void *content);
int				dict_set_default(t_list *lst, char *key, char *value);
struct s_dict	*new_dict(char *key, char *value);
int				cmp_dict_keys(void *content, void *ref);
void			dict_print(void *content);
char			*dict_value(void *data);
char			*dict_to_str(void *data);

int				display_err(struct s_process *ps);

int				dict_add_back(t_list **env, struct s_dict *content);
int				upload_env_to_dict(char **envp, t_list **env);
void			env_dict_print(void *content);
char			*env_pull_to_str(struct s_dict *content);

void			count_redirections(void *proc, void *redirs);

/* builtins 	*/
int				msh_echo(struct s_process *ps);
int				msh_export(struct s_process *ps);
int				msh_unset(struct s_process *ps);
int				msh_env(struct s_process *ps);
int				msh_pwd(struct s_process *ps);
int				msh_cd(struct s_process *ps);
int				msh_exit(struct s_process *ps);
int				msh_heredoc(struct s_process *ps);

void			free_process(void *proc);

t_flags			_init_flags(void);
int				_start_shell(t_shell *shell);

/* parser */	
int				pre_parser(char *line, t_shell *shell);
void			main_parser(char *line, t_shell *shell, t_token **token);
int				check_cmd(char *line, t_shell *shell);
int				parse_cmd(char *line, t_shell *shell);
int				parse_single_quotes(char *line, t_shell *shell);
int				parse_double_quotes(char *line, t_shell *shell);
int				parse_env_sign(char *line, t_shell *shell);
int				parse_redirect(char *line, t_shell *shell);
int				parse_pipe(char *line, t_shell *shell);

char			*add_env_to_str(char *line, t_shell *shell);
int				check_for_env(char **line, t_shell *shell);
void			free_env_shell(t_shell *shell);
void			join_env_string(t_shell *shell, char *line);

void			set_flags(struct s_process *new, t_shell *shell);
int				get_env(t_shell *shell, char *line, int i, int end);

/* command */
int				init_command(t_shell *shell);
int				compose_command(t_list **cmds, t_token *token, t_shell *shell);
void			free_command(t_cmd **list);
void			print_command(t_shell *shell);

/* check_cmd	 */
int				pipe_syntax(char *line, int i, t_shell *shell);
int				redir_syntax(char *line, int i, t_shell *shell);
void			single_quote(char *line, int i, t_shell *shell);
void			double_quote(char *line, int i, t_shell *shell);

/* token */
t_token			*token_lstlast(t_token *lst);
t_token			*token_lstadd(t_token **lst, char *line, t_shell *shell);
int				token_lstsize(t_token *lst);
void			token_lstclear(t_token **list);
char			*token_strjoin(char *rmd, char *buffer);
void			print_token(t_token *token);

/* util */
int				space_skip(const char *nptr, int index);
void			ft_putendl(char *s, int endl);
int				error_out(t_shell *shell);
int				set_error(t_shell *shell, int error);
void			free_and_null(char *str1, char *str2);

/* signals */
void			do_signals(int sig);

/* redirects	 */
int				check_redir(t_token *token,
					struct s_process **new, t_shell *shell);

int				heredoc_test(t_shell *shell, char *stop);
size_t			ft_strlen2(const char *s);
int				heredoc_comp(t_shell *shell, char *stop);
int				heredoc_init(t_shell *shell, char *stop);

int				exec_heredoc(struct s_process *ps);

int				check_env_syntax(char *line, int i);

#endif
