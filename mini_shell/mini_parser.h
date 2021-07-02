#ifndef MINI_PARSER_H
# define MINI_PARSER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
//# include <sys/types.h>
//# include <sys/wait.h>

# define BUFFER_SIZE 42
# define DQ	50 // ""
# define SQ	51 // ''
# define SR 52 // >
# define RR 53 // >>
# define IN 54 // <
# define SC 55 // ;
# define EN 56 // $
# define BS 57 // '\\'

typedef	struct s_par
{
	int	single_q;
	int	double_q;
	int	has_pipe;
	int	pipe_count;
	int	has_env;
	int	back_slash;
	int	has_redir;
	int	double_redir;
	int	semi_colon;
}	t_par;

typedef	struct s_list
{
	char			*cmd;
	int				i;
	int				c_type;
	struct s_list	*next;
}	t_list;

typedef	struct s_env
{
	char			*key;
	char			*value;
	int				len;
	struct s_env	*next;
}	t_env;


typedef struct s_shell
{
	t_list	*cmd;
	t_env	*env;
	t_par	pars;
	char	**args;
	char	*env_value;
	int		fd_i;
	int		fd_o;
	int		*fd;
	int		*fd2;
	int		pipe[2];
	int		status;
	int		err;
	int		dq_err;
	int		sq_err;
	int		arg_size;
	int		env_len;
	int		env_sign;
	int		i;
	int		start;
	int		end;
}	t_shell;

//GNL UTILS
size_t	ft_strlen_endl(char *str);
size_t	ft_strlen(const char *s);
int	ft_strendl(char *str);
char	*ft_strjoin(char *rmd, char *buffer);

//GNL
int	get_next_line(int fd, char **line);
char	*ft_join_line(char *rmd);
char	*ft_rewrite_rmd(char *rmd);

//MINISHELL
int		start_shell(t_shell *shell);
int	mini_exec(char **line, t_shell *shell);
int		mini_cmd(t_shell *shell);

//PARSER
int		mini_parser(char *line, t_shell *shell);
int		check_cmd(char *line, t_shell *shell);
//void	parse_cmd(char *line, int *i, t_shell *shell);
int		parse_cmd(char *line, t_list **cmd, t_shell *shell);
int		parse_single_quotes(char *line, t_list **cmd, t_shell *shell);
int		parse_double_quotes(char *line, t_list **cmd, t_shell *shell);
int	parse_env_sign(char *line, t_list **cmd, t_shell *shell);

char	*add_env_to_str(char *line, t_shell *shell);
int	check_for_env(char **line, t_shell *shell);

//ENV
void	init_env(char **envp, t_shell *shell);
void	env_parser(char **envp, t_env **env);
t_env	*ft_env_list(t_env **lst, char *line, int j, int end);
void	ft_env(t_shell *shell);
char	*get_env(t_shell *shell, char *line, int i, int end);
void	ft_env_clear(t_env **list);

int		check_env_syntax(char *line, int i);
int		ifkey(char c);



char	**make_map(t_list *head, int size, t_shell *shell);
void	clear_map(char **map, int size);

int	error_out(t_shell *shell, char *error);

//UTILS
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putendl(char *s, int endl);
int		space_skip(const char *nptr, t_shell *shell);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
int		ft_isalnum(int c);

//LIST STUFF
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstadd(t_list **lst, char *line, t_shell *shell);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **list);

#endif