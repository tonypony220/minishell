#include <sys/wait.h>
#include <sys/ioctl.h>

int main()
{
	ioctl()
	waitpid(5)
	pid_t pid;

    pid = fork();
    if (pid == -1) { 
	/* fork error - cannot create child */
	perror("Demo program");
	exit(1);
	}
    else if (pid == 0) {
     /* code for child */
	/* probably a few statements then an execvp() */ 
	_exit(1);  /* the execvp() failed - a failed child
                      should not flush parent files */
	}
    else { /* code for parent */ 
        printf("Pid of latest child is %d\n", pid);
            /* more code */
	exit(0);
        }
}

int func()
{
	int fd[2];

	if (pipe(fd) == -1)    
	{
		perror("demo");
		exit(1);
	}
	if ((pid = fork()) == -1)
	{
		perror("demo");
		exit(1);
	}
	else if (pid == 0)   				/* child:  "cat a"                      */
	{  
		close(fd[0]);    				/* close read end of pipe               */
		dup2(fd[1],1);   				/* make 1 same as write-to end of pipe  */
		close(fd[1]);    				/* close excess fildes                  */
		execlp("cat","cat","a",NULL);
		perror("demo");  				/* still around?  exec failed           */
		_exit(1);        				/* no flush                             */
	}
	else 
	{                      				/* parent:  "/usr/bin/wc"               */
		close(fd[1]);    				/* close write end of pipe              */
		dup2(fd[0],0);   				/* make 0 same as read-from end of pipe */
		close(fd[0]);    				/* close excess fildes                  */
		execlp("/usr/bin/wc","wc",NULL);
		perror("demo");    			    /* still around?  exec failed           */
		exit(1);	        			/* parent flushes                       */
	}
}
