#include <sys/wait.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//extern char** environ;
int	err(char* err_str)
{
	perror(err_str);
	exit(1);
	return 1;
}

int func()
{
	int pid;
	//char **args = {"booo", ""};

	//char *str = malloc(200);
	if ((pid = fork()) == -1)
	{
		perror("demo");
		exit(1);
	}
	else if (pid == 0)   				/* child:  "cat a"                      */
	{  
		//execve(args[0], args, environ);
		sleep(3);
		printf("%d\n", getppid());
		system("leaks forks");
		sleep(1000);
		exit(1);        				/* no flush                             */
	}
	else 
	{                      				/* parent:  "/usr/bin/wc"               */
		printf("%d\n", getppid());
		sleep(1000);
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
