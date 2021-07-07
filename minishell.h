
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
# define SHELL_NAME

//int last_exit_code;

struct		vars
{
	int		last_exit_code;
	struct process **ps;
};

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
	t_list	*env;	   /* back link on current shell evniron */
};


struct		dict
{
	char	*key;
	char	*value;
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

			/* dict and env functions */
t_list		*get_dict_by_key(t_list *lst, void* (*f)(void *), char* key);
void		del_dict(void* content);
char		*dict_key(void* content);
int			dict_set_default(t_list *lst, char* key, char* value);
struct dict	*new_dict(char *key, char *value);
int			cmp_dict_keys(void* content, void* ref);
void		dict_print(void* content);

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

#endif
