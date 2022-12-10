#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
	printf("Beginning (pid:%d)\n", (int) getpid() );
	int x = 100;
	
	int rc = fork();
	if (rc < 0)
	{
		fprintf(stderr, "fork error\n");
		exit(1);
	} 
	else if (rc == 0)									// child
	{
		printf("Child x = %d\n", x);
		x = 101;
		printf("Child x = %d\n", x);
	}
	else												// parent
	{
		// int rc_wait = wait(NULL);
		x = 102;
		printf("Parent x = %d\n", x);
	}
	
	printf("Value x = %d\n", x);
	
	return 0;
}