#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

#define OUT 1
#define IN 0
#define CHILD_PID 0 
/* commands 
 * cat >> file 
 * ls | less >> file
 * echo 
 */
extern char** environ;

int	err(char* err_str)
{
	perror(err_str);
	exit(1);
	return 1;
}

int		new_process(char **args, int fd[2])
{
	/* param fd: waiting only fd to redirect, else 0 */

	int	pid, wpid;
	int status;

	//printf("pid %d %d\n", getpid(), 0);
	
	//!dup2(fd[1], 1) || err("dup");

	if ((pid = fork()) == -1)
	{
		perror("demo");
		exit(1);
	}
	else if (pid == CHILD_PID)
	{
//  	printf("parent pid %d getpid %d getppid %d\n", pid, getpid(), getppid());
//

//		fd[OUT] = open("text", O_WRONLY | O_APPEND);
//		int d = dup2(fd[1], 1);
//		printf("%d<<\n", d);
//	
		printf("%d %d fds\n", fd[IN], fd[OUT]);

		fd[OUT] && ((dup2(fd[OUT], OUT) >= 0) || err("dup2")) && close(fd[OUT]);   	
		fd[IN] && ((dup2(fd[IN], IN) >= 0) || err("dup2")) && close(fd[IN]);   	

		if (execve(args[0], args, environ) == -1)
            err("Could not execve");
	}

	else 					/* parent pid = child pid */
	{

//		wpid = waitpid(pid, &status, WUNTRACED);
	
		if (WIFEXITED(status))  
										/* WIFEXITED True if the process terminated 
										 * normally by a call to _exit(2) or exit(3).
										 * If WIFEXITED(status) is true, WEXITSTATUS evaluates to the low-order 
			 					 		 * 8 bits of the argument passed to _exit(2) or exit(3) by the child. */

		   printf("Exit status: %d\n", WEXITSTATUS(status));  

		else if (WIFSIGNALED(status)) 
										/* WIFSIGNALED True if the process terminated 
										 * due to receipt of a signal. */

			psignal(WTERMSIG(status), "Exit signal");
	}

	return 1;
}

int main(void)
{

	char *line;
//    char **args;
    int status;

//	while (status)
//    printf("> ");
//    line = lsh_read_line();
//    args = lsh_split_line(line);
//    status = lsh_execute(args);
//
//    free(line);
//    free(args);

	char *args[3] = {"/bin/cat", "text", 0};
	char *args2[3] = {"/usr/bin/less", 0, 0};
	int fd[2] = {0, 0};
//	fd[OUT] = open("text", O_WRONLY | O_APPEND);

	/* pipe() return 0 if success */
	(pipe(fd) == -1) && err("pipe creation failed");

	int fd2[2] = {fd[0], fd[1]};

	//printf("fds %d\n", fd[OUT], fd[IN]);
	fd[0] = 0;
	fd2[1] = 0;
	new_process(args, fd); 
	wait(&status);
	close(fd[1]);
	new_process(args2, fd2);
	wait(NULL);		
	close(fd[0]);
}










