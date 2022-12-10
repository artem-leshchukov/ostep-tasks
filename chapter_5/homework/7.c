#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	int rc = fork();
	if (rc < 0)
	{
		fprintf(stderr, "fork error\n");
		exit(1);
	} 
	else if (rc == 0)									// child
	{
		printf("Child (pid:%d)\n", (int)getpid());
		close(STDOUT_FILENO);
	}
	else												// parent
	{	
		int rc_wait = wait(NULL);
		printf("Parent rc_wait:%d (pid:%d)\n", rc_wait, (int)getpid());
	}
	return 0;
}