#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	close(STDOUT_FILENO);
	open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	
	int rc = fork();
	if (rc < 0)
	{
		fprintf(stderr, "fork error\n");
		exit(1);
	} 
	else if (rc == 0)									// child
	{		
		printf("Child (pid:%d)\n", (int)getpid());
	}
	else												// parent
	{	
		int rc_wait = wait(NULL);
		printf("Parent (pid:%d)\n", (int)getpid());
	}
	return 0;
}