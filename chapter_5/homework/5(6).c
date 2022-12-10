#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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
		int rc_wait = wait(NULL);
		printf("Child rc_wait:%d (pid:%d)\n", rc_wait, (int)getpid());
	}
	else												// parent
	{	
		int* status;
		int rc_wait = waitpid(getpid()+1, status, 0);
		printf("Parent rc_wait:%d (pid:%d)\n", rc_wait, (int)getpid());
	}
	return 0;
}