#include <sys/wait.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	err(char* err_str)
{
	perror(err_str);
	exit(1);
	return 1;
}

int func()
{
	int fd[2];
	int pid;
	int a;

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
		a = dup2(fd[1],1);   			/* make 1 same as write-to end of pipe  */
		a <= 0 ||  write(1, "more", 4);						
		close(fd[1]);    				/* close excess fildes                  */
		execlp("cat","cat","a",NULL);
		perror("demo");  				/* still around?  exec failed           */
		_exit(1);        				/* no flush                             */
	}
	else 
	{                      				/* parent:  "/usr/bin/wc"               */
		close(fd[1]);    				/* close write end of pipe              */
		a = !dup2(fd[0],0);   				/* make 0 same as read-from end of pipe */
		printf("%d<<", a);
		close(fd[0]);    				/* close excess fildes                  */
		//execlp("/usr/bin/wc","wc",NULL);
		//err("err");    			    /* still around?  exec failed           */
		exit(1);	        			/* parent flushes                       */
	}
}

int main()
{

	func();
//	ioctl()
//	waitpid(5)
//	pid_t pid;

//    pid = fork();
//    if (pid == -1) 
//	{ 
//		/* fork error - cannot create child */
//		perror("Demo program");
//		exit(1);
//	}
//    else if (pid == 0) {
//		 /* code for child */
//		/* probably a few statements then an execvp() */ 
//		_exit(1);  /* the execvp() failed - a failed child
//						  should not flush parent files */
//	}
//    else 
//	{ 
//	/* code for parent */ 
//    	printf("Pid of latest child is %d\n", pid);
//            /* more code */
//	exit(0);
//       }
}
