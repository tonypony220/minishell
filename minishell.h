#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include "libft/libft.h"
#include <sys/stat.h>

#define OUT 1
#define IN 0
#define CHILD_PID 0

#define WAIT 1 << 1
#define REDIRECT 1 << 2
#define W_FILE 1 << 3
#define R_FILE 1 << 4
#define A_FILE 1 << 5  /* append to dile */

struct		process
{
	char	**args;
	int		pipe[2];  /* pipe number ex.: 1 pipe in, 2 pipe out */
				      /* when pipe not used it will be -1 */
	int		fd[2];
	int		**fds; 	  /* all fds inherited from parent process pipe() */
				  	  /* mapping would be pipe number = fds index + 1 */
	int		status;
	char	*file;    /* filename to redirections */
};

int arr_len(void **p);
int path_executable(char *name);
char *find_path(char *name);
void tst_find_path(void);
int freemultalloc(void **p);
void **multalloc(int rows, int columns, unsigned long size);
