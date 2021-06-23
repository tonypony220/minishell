#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include "libft/libft.h"
#include <sys/stat.h>
#include <sysexits.h>
#include <sys/errno.h>

#define RED 	"\033[1;31m"
#define GREEN  	"\033[0;32m"
#define RESET  	"\033[0;0m"
#define BOLD   	"\033[;1m"
#define REVERSE "\033[;7m"

#define CMD_NOT_FOUND_CODE 127

#define OUT 1
#define IN 0
#define CHILD_PID 0
#define WAIT 1 << 1
#define COMMAND 1 << 2
//#define REDIRECT 1 << 2
//#define W_FILE 1 << 3
//#define R_FILE 1 << 4
#define A_FILE 1 << 5  /* append to dile */
#define SEQ 1 << 6	/* process terminates ';'. and not concurent executing */
#define BUILTIN 1 << 7
#define DIRECT 1 << 8  /*  */

#define BUILTINS "env echo pwd export unset exit"
#define WR_BUILTINS "env echo pwd"  			/* which write */
#define SELF_BUILTINS "export unset exit"  	/* which execute */
#define UPPER_BUILTINS "ENV ECHO PWD CD"  		/* which has upper aliases */
#define UPPER_EXCLUDED_BUILTINS "EXPORT UNSET EXIT"  /* which has not upper aliases */

int last_exit_code;

struct		process
{
	char	**args;
	int		pipe[2];  /* pipe number ex.: 1 pipe in, 2 pipe out */
				      /* when pipe not used it will be -1 */
	int		fd[2];
	int		**fds; 	  /* all fds inherited from parent process pipe() */
				  	  /* mapping would be pipe number = fds index + 1 */
	int		status;
	int		exit_code; /* reserved unix exit code
	                   * https://tldp.org/LDP/abs/html/exitcodes.html   */
	char	*file;    /* filename to redirections */
};


struct				dict
{
	char			*key;
	char			*value;
};


void		ft_str_to_lower(char *str);
int			arr_len(void **p);
int			path_executable(char *name);
char		*find_path(char *name);
void		tst_find_path(void);
int			freemultalloc(void **p);
void		**multalloc(int rows, int columns, unsigned long size);
int			printmultalloc(void **p);

int			yosh_echo(struct process *ps);

			/* dict functions */
t_list					*get_dict_by_key(t_list *lst, void* (*f)(void *), char* key);
void					del_dict(struct dict* content);
t_list					*del_dict_by_key(t_list *lst, void (*del)(void *),
											void* (*f)(void *), char* key);
void					*dict_key(struct dict* content);
int						dict_set_default(t_list *lst, char* key, char* value);
void					env_content_print(struct dict* content);
struct dict				*new_dict(char *key, char *value);
void					upload_env_to_dict(char **envp, t_list **env);
int						cmp_dict_keys(struct dict* content, struct dict* ref);
t_list	*ft_lst_find(t_list *lst, void *data_ref, int (*cmp)());
void	ft_lst_rm(t_list **lst, void *data_ref, 
					int (*cmp)(), void (*del)(void *));

void	ft_list_remove_if(t_list **lst, 
							void *data_ref, 
							int (*cmp)(),
							void (*free_fct)(void *));
